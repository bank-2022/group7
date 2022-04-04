var express = require("express");
var path = require("path");
var cookieParser = require("cookie-parser");
var logger = require("morgan");

var helmet = require("helmet");
var cors = require("cors");

var usersRouter = require('./routes/users');
var asiakasRouter = require("./routes/asiakas");
var korttiRouter = require('./routes/kortti');

var app = express();

app.use(logger("dev"));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, "public")));

app.use(helmet());
app.use(cors());

app.use('/users', usersRouter);
app.use("/asiakas", asiakasRouter);
app.use('/kortti', korttiRouter);


module.exports = app;
