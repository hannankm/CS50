import os


# check if shares is integer when buying and selling stock
from cs50 import SQL
from datetime import datetime
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # rows = db.execute("SELECT id, symbol, SUM(shares)  FROM transactions WHERE id = ? GROUP BY symbol HAVING SUM(shares) > 0 ORDER BY price DESC", session["user_id"])
    rows = db.execute("SELECT * FROM stock WHERE user_id = ?", session["user_id"])

    user = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

    total = user[0]["cash"]
    for i in range(len(rows)):
        rows[i].update({"price": lookup(rows[i]["symbol"])["price"]})
        rows[i].update({"value": rows[i]["shares"]*rows[i]["price"]})
        total += rows[i]["shares"] * lookup(rows[i]["symbol"])["price"]
    return render_template("index.html", cash=user[0]["cash"], stocks=rows, total=round(total, 2))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        if not request.form.get("shares") or not request.form.get("symbol"):
            return apology("Enter required fields symbol and shares")

        if lookup(request.form.get("symbol")) == None:
            return apology("Symbol is invalid")

        try:
            if int(request.form.get("shares")) < 1:
                return apology("Shares value should be greater than one")
        except ValueError:
            return apology("Shares should be a whole number")

        rows = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        quote = lookup(request.form.get("symbol"))

        amount = float(quote["price"]) * int(request.form.get("shares"))
        wallet = rows[0]["cash"]
        remaining = wallet - amount

        if amount > wallet:
            return apology("You can't afford this")
        #  record transactions in new table and update user's cash

        db.execute("INSERT INTO transactions (user_id, symbol, price, shares, timestamp, type) VALUES (?, ?, ?, ?, ?, 'Purchase')",
                   session["user_id"], quote["symbol"], quote["price"], request.form.get("shares"), datetime.now())
        db.execute("UPDATE users SET cash = ? WHERE id = ?", round(remaining, 2), session["user_id"])

        # record ownership in stock table
        rows = db.execute("SELECT * FROM stock WHERE user_id = ? AND symbol = ?", session["user_id"], quote["symbol"])
        if len(rows) == 0:
            db.execute("INSERT INTO stock (user_id, symbol, shares) VALUES (?, ?, ?)",
                       session["user_id"], quote["symbol"], request.form.get("shares"))
        else:
            db.execute("UPDATE stock SET shares = ? WHERE user_id = ? AND symbol = ?",
                       rows[0]["shares"] + int(request.form.get("shares")), session["user_id"], quote["symbol"] )
        flash('Bought!')
        return redirect("/")
    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute("SELECT * FROM transactions WHERE user_id = ?", session["user_id"])
    return render_template("history.html", transactions=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("Must provide symbol")
        try:
            if lookup(request.form.get("symbol")) == None:
                return apology("Symbol is invalid")
        except TypeError:
            return apology("Symbol is invalid")
        quotes = lookup(request.form.get("symbol"))

        return render_template("quoted.html", quotes=quotes)
    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("Must provide username")
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        if len(rows) > 0:
            return apology("Username is already taken")
        if not request.form.get("password") or not request.form.get("confirmation"):
            return apology("Must provide password")
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("Passwords don't match")
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", request.form.get(
            "username"), generate_password_hash(request.form.get("confirmation")))
        flash('Registered!')
        return redirect("/")
    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    stocks = db.execute("SELECT symbol from stock WHERE user_id = ?", session["user_id"])
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("Must provide symbol")
        if not request.form.get("shares"):
            return apology("Must provide shares")
        try:
            if int(request.form.get("shares")) < 1:
                return apology("Shares value should be greater than one")
        except ValueError:
            return apology("Shares should be a whole number")
        rows = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        # GET CURRENT PRICE
        quote = lookup(request.form.get("symbol"))
        amount = float(quote["price"]) * int(request.form.get("shares"))
        # ADD TO CASH
        wallet = rows[0]["cash"]
        remaining = wallet + amount
        db.execute("UPDATE users SET cash = ? WHERE id = ?", round(remaining, 2), session["user_id"])
        # RECORD TRANSACTION
        db.execute("INSERT INTO transactions (user_id, symbol, price, shares, timestamp, type) VALUES (?, ?, ?, ?, ?, 'Sale')",
                   session["user_id"], quote["symbol"], quote["price"], request.form.get("shares"), datetime.now())
        # update ownership
        rows = db.execute("SELECT * FROM stock WHERE user_id = ? AND symbol = ?", session["user_id"], quote["symbol"])
        if len(rows) == 0:
            return apology("You don't have any shares of this stock")
        if rows[0]["shares"] < int(request.form.get("shares")):
            return apology("You don't have enough shares of this stock")
        if rows[0]["shares"] == int(request.form.get("shares")):
            db.execute("DELETE FROM stock WHERE user_id = ? AND symbol = ?", session["user_id"], quote["symbol"])
            return redirect("/")
        db.execute("UPDATE stock SET shares = ? WHERE user_id = ? AND symbol = ?",
                   rows[0]["shares"] - int(request.form.get("shares")), session["user_id"], quote["symbol"])
        flash('Sold!')
        return redirect("/")
    return render_template("sell.html", stocks=stocks)