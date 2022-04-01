const db = require('../database');
const bcrypt = require('bcryptjs');

const saltRounds=10;
const kortti={
  get: (callback) => {
    return db.query('select * from kortti', callback);
  },
  getById: (id, callback) => {
    return db.query('select * from kortti where idKortti=?', [id], callback);
  },
  add: (kortti, callback) => {
    bcrypt.hash(kortti.pin, saltRounds, (err, hash) => {
      return db.query('insert into kortti (pin, idTilinumero, idAsiakas) values(?,?,?)',
      [hash, kortti.idTilinumero, kortti.idAsiakas], callback);
    });
  },
  delete: (id, callback) => {
    return db.query('delete from kortti where idKortti=?', [id], callback);
  },
  update: (id, kortti, callback) => {
    bcrypt.hash(kortti.pin, saltRounds, (err, hash) => {
      return db.query('update kortti set pin=?, idTilinumero=?, idAsiakas=?  where idKortti=?',
      [hash, kortti.idTilinumero, kortti.idAsiakas, id], callback);
    });
  }

}
          
module.exports = kortti;