import mqtt from "mqtt/dist/mqtt";

const options = {
  port: 5050,
  clientId: "sebben",
  clean: false,
};

let client = mqtt.connect("ws:aedes-broker.cloud.mustini.se", options); // create a client

export { client };
