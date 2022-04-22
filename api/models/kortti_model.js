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
  getAsiakasByKortti(id, callback) {
    return db.query("select asiakas.idAsiakas, nimi, osoite, puhelinnumero from kortti inner join asiakas on asiakas.idAsiakas = kortti.idAsiakas where kortti.idKortti = ?",
    [id], callback);
  },
  getTiliByKortti(id, callback) {
    return db.query("select tili.idTilinumero, saldo from kortti inner join tili on tili.idTilinumero = kortti.idTilinumero where kortti.idKortti = ?",
    [id], callback);
  },
  add: (kortti, callback) => {
    bcrypt.hash(kortti.pin, saltRounds, (err, hash) => {
      return db.query('insert into kortti (idKortti, pin, idTilinumero, idAsiakas) values(?,?,?,?)',
      [kortti.idKortti, hash, kortti.idTilinumero, kortti.idAsiakas], callback);
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
