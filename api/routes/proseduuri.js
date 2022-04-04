var express = require("express");
var router = express.Router();
var proseduuri = require("../models/proseduuri_model");

router.post("/nosto", (req, res) => {
  proseduuri.nosto(req.body, (err, dbResult) => {
    if (err) {
      res.json(err);
    } else {
      res.json(dbResult);
    }
  });
});

router.post("/talletus", (req, res) => {
  proseduuri.talletus(req.body, (err, dbResult) => {
    if (err) {
      res.json(err);
    } else {
      res.json(dbResult);
    }
  });
});

router.post("/tilisiirto", (req, res) => {
    proseduuri.tilisiirto(req.body, (err, dbResult) => {
      if (err) {
        res.json(err);
      } else {
        res.json(dbResult);
      }
    });
  });

  module.exports = router;