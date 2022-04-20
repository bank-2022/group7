const db = require("../database");

const proseduuri = {
  nosto(proseduuri, callback) {
    return db.query(
      "call nosto(?, ?, ?)",
      [proseduuri.kortinnro, proseduuri.tilinro, proseduuri.rahasumma],
      callback
    );
  },

  talletus(proseduuri, callback) {
    return db.query(
      "call talletus(?, ?, ?)",
      [proseduuri.kortinnro, proseduuri.tilinro, proseduuri.rahasumma],
      callback
    );
  },

  tilisiirto(proseduuri, callback) {
    return db.query(
      "call tilisiirto(?, ?, ?, ?)",
      [
        proseduuri.kortinnro,
        proseduuri.sendertilinro,
        proseduuri.receivertilinro,
        proseduuri.rahasumma,
      ],
      callback
    );
  },
};

module.exports = proseduuri;
