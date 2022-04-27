const db = require('../database');

const tili = {
  getAll: function(callback) {
    return db.query('select * from tili', callback);
  },
  getByTilinumero: function(id, callback) {
    return db.query('select * from tili where idTilinumero = ?', [id], callback);
  },
  getSaldo(id, callback) {
    return db.query('select saldo from tili where idTilinumero = ?', [id], callback);
  },
  add: function(tili, callback) {
    return db.query(
      'insert into tili (idTilinumero, saldo) values(?,?)',
      [tili.idTilinumero, tili.saldo],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from tili where idTilinumero = ?',
     [id], callback);
  },
 
  update: function(id, tili, callback) {
    return db.query(
      'update tili set idTilinumero = ?, saldo =? WHERE idTilinumero=?',
      [tili.idTilinumero, tili.saldo, id],
      callback
    );
  }

};
 
module.exports = tili;