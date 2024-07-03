import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
import datetime

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
    user_id = session["user_id"]

    transactions = db.execute(
        "SELECT symbol, SUM(shares) AS total_shares FROM transactions WHERE user_id = ? GROUP BY symbol HAVING total_shares > 0",
        user_id,
    )
    user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    cash = user_cash[0]["cash"]

    total_value = cash
    grand_total = cash

    for transaction in transactions:
        quote = lookup(transaction["symbol"])
        transaction["name"] = quote["name"]
        transaction["price"] = quote["price"]
        transaction["value"] = transaction["price"] * transaction["total_shares"]
        total_value += transaction["value"]
        grand_total += transaction["value"]

    return render_template(
        "index.html",
        transactions=transactions,
        cash=cash,
        total_value=total_value,
        grand_total=grand_total,
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")

        if not symbol:
            return apology("must provide a symbol")

        quote = lookup(symbol)
        if quote == None:
            return apology("The lookup was unsuccessful")

        if not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("provide a valid number of shares")

        price = quote["price"]
        cost = int(shares) * price

        user_id = session["user_id"]
        user_cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        user_cash = user_cash_db[0]["cash"]

        if user_cash < cost:
            return apology("you don't have enough money")

        cash_now = user_cash - cost
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash_now, user_id)

        date = datetime.datetime.now()
        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?)",
            user_id,
            symbol,
            shares,
            price,
            date,
        )

        flash(f"Bought for {usd(cost)}!")

        return redirect("/")
    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    transactions = db.execute("SELECT * FROM transactions WHERE user_id = ?", user_id)
    return render_template("history.html", transactions=transactions)


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
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
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
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide a symbol")

        quote = lookup(symbol.upper())
        if quote == None:
            return apology("The lookup was unsuccessful")

        return render_template("quoted.html", quote=quote)
    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("Must provide a username")

        if not password:
            return apology("Must provide password")

        if not confirmation:
            return apology("Please, confirm your password")

        if password != confirmation:
            return apology("Passwords do not match")

        if (
            len(db.execute("SELECT username FROM users WHERE username = ?", username))
            != 0
        ):
            return apology("Username already taken")

        new_user = db.execute(
            "INSERT INTO users (username, hash) VALUES (?, ?)",
            username,
            generate_password_hash(password),
        )

        session["user_id"] = new_user
        return redirect("/")
    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]
    transactions = db.execute(
        "SELECT symbol, SUM(shares) AS total_shares FROM transactions WHERE user_id = ? GROUP BY symbol HAVING total_shares > 0",
        user_id,
    )

    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")

        if not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("provide a valid number of shares")

        elif not symbol:
            return apology("must provide a symbol")

        else:
            shares = int(shares)

        for transaction in transactions:
            if transaction["symbol"] == symbol:
                if transaction["total_shares"] < shares:
                    return apology("you do not have enough shares")
                quote = lookup(symbol)
                if quote == None:
                    return apology("lookup was unsuccessfull")
                price = quote["price"]
                total_sale = shares * price

                user_cash_db = db.execute(
                    "SELECT cash FROM users WHERE id = ?", user_id
                )
                user_cash = user_cash_db[0]["cash"]

                cash_now = user_cash + total_sale

                db.execute("UPDATE users SET cash = ? WHERE id = ?", cash_now, user_id)

                date = datetime.datetime.now()
                db.execute(
                    "INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?)",
                    user_id,
                    symbol,
                    shares,
                    price,
                    date,
                )

                flash(f"Sold for {usd(total_sale)}!")
                return redirect("/")

            return apology("symbol not found")

    return render_template("sell.html", transactions=transactions)
