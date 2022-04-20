var express = require("express");
var router = express.Router();
var asiakas = require("../models/asiakas_model");

router.get("/:id?", (req, res) => {
  if (req.params.id) {
    asiakas.getById(req.params.id, (err, dbResult) => {
      if (err) {
        res.json(err);
      } else {
        res.json(dbResult[0]);
      }
    });
  } else {
    asiakas.getAll((err, dbResult) => {
      if (err) {
        res.json(err);
      } else {
        res.json(dbResult);
      }
    });
  }
});

router.post("/", (req, res) => {
  asiakas.add(req.body, (err, dbResult) => {
    if (err) {
      res.json(err);
    } else {
      res.json(dbResult);
    }
  });
});

router.delete("/:id", (req, res) => {
  asiakas.delete(req.params.id, (err, dbResult) => {
    if (err) {
      res.json(err);
    } else {
      res.json(dbResult);
    }
  });
});

router.put("/:id", (req, res) => {
  asiakas.update(req.params.id, req.body, (err, dbResult) => {
    if (err) {
      res.json(err);
    } else {
      res.json(dbResult);
    }
  });
});

module.exports = router;
