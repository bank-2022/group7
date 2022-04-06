var express = require("express");
var path = require("path");
var cookieParser = require("cookie-parser");
var logger = require("morgan");
var jwt = require('jsonwebtoken');

var helmet = require("helmet");
var cors = require("cors");

var loginRouter = require('./routes/login');
var usersRouter = require("./routes/users");
var asiakasRouter = require("./routes/asiakas");
var korttiRouter = require("./routes/kortti");
var proseduuriRouter = require("./routes/proseduuri");
var tilitapahtumaRouter = require("./routes/tilitapahtuma");

var app = express();

app.use(logger("dev"));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, "public")));

app.use(helmet());
app.use(cors());

app.use('/login', loginRouter);
app.use(authenticateToken)
app.use("/users", usersRouter);
app.use("/asiakas", asiakasRouter);
app.use("/kortti", korttiRouter);
app.use("/proseduuri", proseduuriRouter);
app.use("/tilitapahtuma", tilitapahtumaRouter);

function authenticateToken(req, res, next) {
    const authHeader = req.headers['authorization']
    const token = authHeader && authHeader.split(' ')[1]
  
    console.log("token = "+token);
    if (token == null) return res.sendStatus(401)
  
    jwt.verify(token, process.env.MY_TOKEN, (err, user) => {
      console.log(err)
  
      if (err) return res.sendStatus(403)
  
      req.user = user
  
      next()
    })
  }

module.exports = app;
