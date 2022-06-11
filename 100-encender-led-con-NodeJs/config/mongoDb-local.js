const mongoose = require('mongoose');
const server = require('./properties');

const Conexion = () => {
    mongoose.connect(server.DB, { useNewUrlParser: true, useUnifiedTopology: true, useCreateIndex: true, useFindAndModify:false}, (e) =>{
        if(e) throw new console.error(e);
            console.log("Base de datos conectada");
    });
}

module.exports = Conexion;