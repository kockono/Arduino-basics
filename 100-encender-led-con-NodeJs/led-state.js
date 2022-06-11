const { Schema, model } = require('mongoose'); // Liberias


const stateLedSchema = new Schema ({
    led: {
        type: Boolean,
    }
});

module.exports = model('StateLeds', stateLedSchema);