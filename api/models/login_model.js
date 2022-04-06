const db = require('../database');

const login={
  checkPin: function(idKortti, callback) {
      return db.query('SELECT pin FROM kortti WHERE idKortti = ?',[idKortti], callback); 
    }
};
          
module.exports = login;