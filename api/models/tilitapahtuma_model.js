const db = require("../database");

const tilitapahtuma = {
  getById(id, callback) {
    return db.query("select * from tilitapahtuma where idTilitapahtuma=?", [id], callback);
  },
  getAll(callback) {
    return db.query("select * from tilitapahtuma", callback);
  },
  add(tilitapahtuma, callback) {
    return db.query(
      "insert into tilitapahtuma (IdTilinumero, dateTime, summa, tilitapahtuma, idKortti) values(?,?,?,?,?)",
      [tilitapahtuma.idTilinumero,tilitapahtuma.dateTime, tilitapahtuma.summa, tilitapahtuma.tilitapahtuma, tilitapahtuma.idKortti],
      callback
    );
  },
  delete(id, callback) {
    return db.query("delete from tilitapahtuma where idTilitapahtuma=?", [id], callback);
  },
  update(id, tilitapahtuma, callback) {
    return db.query(
      "update tilitapahtuma set IdTilinumero=?, dateTime=?, summa=?, tilitapahtuma=?, idKortti=?, where idTilitapahtuma=?",
      [tilitapahtuma.idTilinumero,tilitapahtuma.dateTime, tilitapahtuma.summa, tilitapahtuma.tilitapahtuma, tilitapahtuma.idKortti, id],
      callback
    );
  },
};

module.exports = tilitapahtuma;