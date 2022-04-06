const db = require("../database");

const asiakas = {
  getById(id, callback) {
    return db.query("select * from asiakas where idAsiakas=?", [id], callback);
  },
  getAll(callback) {
    return db.query("select * from asiakas", callback);
  },
  add(asiakas, callback) {
    return db.query(
      "insert into asiakas (nimi, osoite, puhelinnumero) values(?,?,?)",
      [asiakas.nimi, asiakas.osoite, asiakas.puhelinnumero],
      callback
    );
  },
  delete(id, callback) {
    return db.query("delete from asiakas where idAsiakas=?", [id], callback);
  },
  update(id, asiakas, callback) {
    return db.query(
      "update asiakas set nimi=?, osoite=?, puhelinnumero=? where idAsiakas=?",
      [asiakas.nimi, asiakas.osoite, asiakas.puhelinnumero, id],
      callback
    );
  },
};

module.exports = asiakas;
