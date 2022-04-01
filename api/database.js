const mysql = require('mysql');
const connection = mysql.createPool({
  host: 'localhost',
  user: 'magus',
  password: 'maaginen',
  database: 'bankautomat'
});
module.exports = connection;