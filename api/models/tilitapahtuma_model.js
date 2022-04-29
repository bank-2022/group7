const db = require('../database');

const tilitapahtuma = {
  getById(id, callback) {
    return db.query("select * from tilitapahtuma where idTilitapahtuma=?", [id], callback);
  },
  getByTilinumero: function(idTilinumero, callback) {
    return db.query('select date_format(tilitapahtuma.dateTime, "%d-%m-%Y  %H:%i:%s") as "aikaleima",summa,tilitapahtuma from bankautomat.tilitapahtuma where idTilinumero = ? order by dateTime desc', [idTilinumero], callback);
  },
  getAll: function(callback) {
    return db.query('select * from tilitapahtuma', callback);
  },
  getByidKortti: function(idKortti, callback) {
    return db.query('select * from tilitapahtuma where idKortti=?', [idKortti], callback)
  },

  add: function(tilitapahtuma, callback) {
    return db.query(
      'insert into tilitapahtuma (idTilinumero, dateTime, summa, tilitapahtuma, idKortti) values(?,?,?,?,?)',
      [tilitapahtuma.idTilinumero, tilitapahtuma.dateTime, tilitapahtuma.summa, tilitapahtuma.tilitapahtuma,
      tilitapahtuma.idKortti],
      callback
    );

  },
  delete: function(tilitapahtuma, callback) {
    return db.query('delete from tilitapahtuma where idTilitapahtuma = ?', 
    [tilitapahtuma], callback);
  },
  update: function(idTilitapahtuma, tilitapahtuma, callback) {
    return db.query(
      'update tilitapahtuma set idTilinumero = ?, dateTime = ?, summa = ?, tilitapahtuma = ?, idKortti = ? WHERE idTilitapahtuma = ?',
      [tilitapahtuma.idTilinumero, tilitapahtuma.dateTime, tilitapahtuma.summa, tilitapahtuma.tilitapahtuma,
      tilitapahtuma.idKortti, idTilitapahtuma],
      callback
    );
  }
};

module.exports = tilitapahtuma;