const mqtt = require("mqtt");
const client = mqtt.connect("mqtt://localhost:1882");

client.on("connect", function () {
  console.log("Connected to Aedes broker!");
  client.subscribe("topic");
  client.publish("topic", "snoppdick");
});



client.on("message", function (topic, message) {
  console.log(`Received message on topic ${topic}: ${message.toString()}`);
});