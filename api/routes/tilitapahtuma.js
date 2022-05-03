const express = require('express');
const router = express.Router();
const tilitapahtuma = require('../models/tilitapahtuma_model');

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

router.get('/tilinumero/:id', function(request, response) {
    if (request.params.id) {
        tilitapahtuma.getByTilinumero(request.params.id, function(err, dbResult) {
        if (err) {
            response.json(err);
        } else {
            response.json(dbResult)
        }
    });       
  }
});

router.get('/nosto/:id', function(request, response) {
  if (request.params.id) {
      tilitapahtuma.getByFiltteriNosto(request.params.id, function(err, dbResult) {
      if (err) {
          response.json(err);
      } else {
          response.json(dbResult)
      }
  })}
});

router.get('/talletus/:id', function(request, response) {
  if (request.params.id) {
      tilitapahtuma.getByFiltteriTalletus(request.params.id, function(err, dbResult) {
      if (err) {
          response.json(err);
      } else {
          response.json(dbResult)
      }
  })}
});

router.get('/siirto/:id', function(request, response) {
  if (request.params.id) {
      tilitapahtuma.getByFiltteriSiirto(request.params.id, function(err, dbResult) {
      if (err) {
          response.json(err);
      } else {
          response.json(dbResult)
      }
  })}
});

router.post('/', 
function(request, response) {
  tilitapahtuma.add(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(request.body);
    }
  });
});

router.delete('/:id', 
function(request, response) {
  tilitapahtuma.delete(request.params.id, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

router.put('/:id', 
function(request, response) {
    tilitapahtuma.update(request.params.id, request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

module.exports = router;
