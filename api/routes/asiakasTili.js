const express = require('express');
const router = express.Router();
const asiakasTili = require('../models/asiakasTili_model');

router.get('/', 
function(request, response) {
  asiakasTili.getAll (function (err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});


    router.get('/:id?', function(request, response) {
      if (request.params.id) {
          asiakasTili.getByAsiakasId(request.params.id, function(err, dbResult) {
          if (err) {
              response.json(err);
          } else {
              response.json(dbResult);
          }
        });   
      } 
      });
 
router.post('/', 
function(request, response) {
  asiakasTili.add(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(request.body);
    }
  });
});


router.delete('/:id?', 
function(request, response) {
  asiakasTili.delete(request.params.id, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});


router.put('/:id', 
function(request, response) {
  asiakasTili.update(request.params.id, request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

module.exports = router;
