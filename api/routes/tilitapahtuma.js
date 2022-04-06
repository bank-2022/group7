var express = require("express");
const tilitapahtuma = require("../models/tilitapahtuma_model");
var router = express.Router();


router.get("/:id?", (req, res) => {
    if (req.params.id) {
      tilitapahtuma.getById(req.params.id, (err, dbResult) => {
        if (err) {
          res.json(err);
        } else {
          res.json(dbResult);
        }
      });
    } else {
      tilitapahtuma.getAll((err, dbResult) => {
        if (err) {
          res.json(err);
        } else {
          res.json(dbResult);
        }
      });
    }
  });

  router.post("/", (req, res) => {
    tilitapahtuma.add(req.body, (err, dbResult) => {
      if (err) {
        res.json(err);
      } else {
        res.json(dbResult);
      }
    });
  });

  router.delete("/:id", (req, res) => {
    tilitapahtuma.delete(req.params.id, (err, dbResult) => {
      if (err) {
        res.json(err);
      } else {
        res.json(dbResult);
      }
    });
  });
  
  router.put("/:id", (req, res) => {
    tilitapahtuma.update(req.params.id, req.body, (err, dbResult) => {
      if (err) {
        res.json(err);
      } else {
        res.json(dbResult);
      }
    });
  });
  
  module.exports = router;