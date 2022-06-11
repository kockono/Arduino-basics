const express = require('express'); // Liberaria para inicializar el servido
const app = express(); // Guarda los metodos en una variable llamada app
const cors = require('cors'); // Nos permite mandar peticiones de frontend a backend
app.use(cors()) // Consume el metodo para inicializar el servidor
var path    = require("path"); // El path de la ruuta
let  ledState  = require('./led-state'); // Aquí se encuentra el modelo del led

let ledOn, stopLed; // Variables para declarar los metodo mas adelante
const connectLocalDB = require('./config/mongoDB-local'); // Importa la configuración de la base de datos
connectLocalDB(); //Consume el metodo para la conexion con la base de datos

app.use(cors({origin: 'http://localhost:4200'})); // Esto nos permitira recibir peticiones del puerto 4200
app.use(express.json()); // Parsea el json
app.use(express.urlencoded({ extended: true })); // recibir peticiones por url

app.get('/', function (req,res) {  
  ledState.findById('611985ae3f3bf0120cae22a5', (err, doc) => { // Encuentra por id en la base de datos
    if(!err) { // Si no recibe un error procesa la siguiente sentencia
      if(doc.led){  //doc contiene el valor de la petición, doc.led tiene el dato de la base de datos
        ledOn() // Manda a llamar el metodo si el estado del led se encontraba activo
      }
    }else {
      console.log(`Error en encontrar el estado del led: `+ JSON.stringify(err, undefined, 2)); // Manda un error 
    }
    });


      res.sendFile(path.join(__dirname+'/index.html')); // Renderiza el index.html y atraves de la variable
      // dirname nos permite conocer la ruta, con path join podra juntar la ruta total para que de esta manera
      // renderize la vista
});

app.get('/ledOn', (req, res) => { // Otro metodo get para encender el led atraves de un boton que se encuentra en html
  let id =  "611985ae3f3bf0120cae22a5"; // la id del led en la base de datos
  ledState.findByIdAndUpdate(id, {led:true}, {new:true} ,(err, doc) => { // Aquí cambiamos el estado a true en la db
    if(!err) {res.send(doc)} // si no existe un error retornara la información
      else { console.log(`Error en encontrar el empleado: `+ JSON.stringify(err, undefined, 2));} // Manda un error
  })
  ledOn() // Manda a llamar el metodo

})

app.get('/ledOff', (req, res) => { // Apaga el led como lo anterior mencionado pero a su inversa
  let id =  "611985ae3f3bf0120cae22a5";
  ledState.findByIdAndUpdate(id, {led:false}, {new:true},(err, doc) => {
    if(!err) {res.send(doc)}
      else { console.log(`Error en encontrar el empleado: `+ JSON.stringify(err, undefined, 2));}

  })

stopLed()

})

app.listen(3000, () => { // Inicializa el server y podemos ver que es declarado en el puerto 3000
  console.log("Server has started and is listening on port 3000")
  })

// Código de Arduino
const { Board, Led } = require("johnny-five"); // Board es el arduino, led es un simple led
var board = new Board({ port: "COM3" });   // Aqui decidimo en que puerto se encuentra el arduino

board.on("ready", () => { // Inicializa el arduino
  const led = new Led(13); // Nos permite decidir en que pin ira el led
  
  ledOn = () => { // Enciende el led
      led.on();
  }

  stopLed = () => { // Detiene y apaga el led
      led.stop()
      led.off()
  }

});



