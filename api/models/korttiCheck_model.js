const db = require('../database');

const kortti={  
  getById: (id, callback) => {
    return db.query('select idKortti from kortti where idKortti=?', [id], callback);
  }
}
          
module.exports = kortti;
