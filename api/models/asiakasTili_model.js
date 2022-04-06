const db = require('../database');

const asiakasTili = {
  getByAsiakasId: function(idAsiakas, callback) {
    return db.query('select * from asiakastili where idAsiakas=?', [idAsiakas], callback);
  },
  getAll: function(callback) {
    return db.query('select * from asiakastili', callback);
  },
  add: function(asiakasTili, callback) {
    return db.query(
      'insert into asiakastili (idAsiakas, idTilinumero) values(?,?)',
      [asiakasTili.idAsiakas, asiakasTili.idTilinumero],
      callback
    );
  },
  delete: function(asiakasTili, callback) {
    return db.query('delete from asiakastili where idAsiakasTili = ?',
     [asiakasTili], callback);
  },
 
  update: function(idAsiakasTili, asiakasTili, callback) {
    return db.query(
      'update asiakastili set idAsiakas=?, idTilinumero=? WHERE idAsiakasTili=?',
      [asiakasTili.idAsiakas, asiakasTili.idTilinumero, idAsiakasTili],
      callback
    );
  }

};
 
module.exports = asiakasTili;