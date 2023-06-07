<template>
  <q-page class="container">
    <div class="flex flex-center">
      <div class="sideInfo q-ma-xl">
        <div class="q-ma-md">
          <q-scroll-area style="height: 600px; max-width: 300px">
            <h3 class="text-weight-bold text-center">Direction</h3>
            <ul>
              <div v-for="i in mqttDir.length" :key="i" class="q-py-xs text-center">
                dir: {{ mqttDir[i] }}
              </div>
            </ul>
          </q-scroll-area>
        </div>
      </div>
      <div>
        <div class="q-pa-md">
          <div style="width: 100%"></div>
        </div>
        <div class=""></div>
        <h1 class="flex flex-center text-weight-bold">Driverbot!</h1>
        <div class="flex row flex-center">
          <div>
            <p class="flex flex-center text-weight-bold text-h5">SPEED</p>
            <q-knob
              v-model="speed"
              show-value
              size="130px"
              :thickness="0.2"
              color="purple-3"
              center-color="purple"
              track-color="purple-1"
              class="q-ma-md"
            />
          </div>

          <div>
            <p class="flex flex-center text-weight-bold text-h5">ANGLE</p>

            <q-knob
              v-model="angle"
              show-value
              size="130px"
              :thickness="0.2"
              color="purple-3"
              center-color="purple"
              track-color="purple-1"
              class="q-ma-md"
            />
          </div>
        </div>
        <div class="flex flex-center q-ma-xl">
          <div class="flex column">
            <div>
              <button
                class="btn arrow-up-left q-ma-xs q-pa-lg"
                @click="move(speed * 10, angle * 1)"
              ></button>
              <button
                class="btn arrow-up q-ma-xs q-pa-lg"
                @click="move(speed * 10, 0)"
              ></button>
              <button
                class="btn arrow-up-right q-ma-xs q-pa-lg"
                @click="move(speed * 10, -angle * 1)"
              ></button>
            </div>
            <div>
              <button
                class="btn arrow-left q-ma-xs q-pa-lg"
                @click="move(0, angle * 1)"
              ></button>
              <button class="q-ma-xs q-pa-lg" @click="move(0, 0)"></button>
              <button
                class="btn arrow-right q-ma-xs q-pa-lg"
                @click="move(0, -angle * 1)"
              ></button>
            </div>
            <div>
              <button
                class="btn arrow-down-left q-ma-xs q-pa-lg"
                @click="move(speed * 10, angle * 1)"
              ></button>
              <button
                class="btn arrow-down q-ma-xs q-pa-lg"
                @click="move(speed * 10, 0)"
              ></button>
              <button
                class="btn arrow-down-right q-ma-xs q-pa-lg"
                @click="move(-speed * 10, -angle * 1)"
              ></button>
            </div>
          </div>
        </div>
      </div>
      <div class="sideInfo q-ma-xl">
        <div class="q-ma-md">
          <q-scroll-area style="height: 600px; max-width: 300px">
            <h3 class="text-weight-bold text-center">Speed</h3>
            <ul>
              <div v-for="i in mqttSpd.length" :key="i" class="q-py-xs text-center">
                speed: {{ mqttSpd[i] }}
              </div>
            </ul>
          </q-scroll-area>
        </div>
      </div>
    </div>
    <div flex>
      <div class="q-ma-xl flex justify-around">
        <div class="sideInfo q-ma-md">
          <q-scroll-area style="height: 600px; max-width: 450px">
            <h3 class="text-weight-bold text-center">Real Direction</h3>
            <ul>
              <div v-for="i in mqttDir.length" :key="i" class="q-py-xs text-center">
                angle: {{ mqttDir[i] }}
              </div>
            </ul>
          </q-scroll-area>
        </div>
        <div class="sideInfo q-ma-md">
          <q-scroll-area style="height: 600px; max-width: 450px">
            <h3 class="text-weight-bold text-center">Conection</h3>
            <ul>
              <div v-for="i in mqttDir.length" :key="i" class="q-py-xs text-center">
                {{ mqttCon[i] }}
              </div>
            </ul>
          </q-scroll-area>
        </div>
        <div class="sideInfo q-ma-md">
          <q-scroll-area style="height: 600px; max-width: 450px">
            <h3 class="text-weight-bold text-center">Real Speed</h3>
            <ul>
              <div v-for="i in mqttDir.length" :key="i" class="q-py-xs text-center">
                speed: {{ mqttSpd[i] }}
              </div>
            </ul>
          </q-scroll-area>
        </div>
      </div>
    </div>
  </q-page>
</template>

<script setup>
import { client } from "src/boot/mqtt-boot";
import { ref, onMounted } from "vue";
let clientVal = "spd";
let speed = 99;
let angle = 50;
let arSpeed = 0;
let arAngle = 0;

let n = 10;
let mqttCon = [];
let mqttSpd = [];
let mqttDir = [];
let mqttarSpd = [];
let mqttarDir = [];
let j = 0;
let h = 0;
let k = 0;
let l = 0;
let m = 0;
console.log("conecting to aedes broker");
mqttCon[0] = "conecting to aedes broker";
//subcripes to to spd (spee) when client is connected
client.on("connect", function () {
  console.log("Connected to Aedes broker!");
  client.subscribe(clientVal);
  m += 1;
  mqttCon[m] = "connected to aedes broker";
});

//when clent is running col the message that has ben recived
client.on("message", function (topic, message) {
  console.log(`Received message on topic ${topic}: ${message.toString()}`);
  m += 1;
  mqttCon[m] = `Received message on topic ${topic}: ${message.toString()}`;

  // if we subscriped to speed that subsccribe to direction
  if (clientVal == "seb/spd") {
    mqttSpd[j] = message.toString();
    console.log(mqttSpd);
    j += 1;
    clientVal = "dir";
  } else if (clientVal == "seb/dir") {
    mqttDir[h] = message.toString();
    console.log(mqttDir);
    h += 1;
    clientVal = "arSpd";
  } else if (clientVal == "seb/arSpd") {
    clientVal = "arDir";
    mqttarDir[k] = message.toString();
    k += 1;
  } else if (clientVal == "seb/arDir") {
    clientVal = "spd";
    mqttarDir[l] = message.toString();
    l += 1;
  }
});

// debentent on witch button is pressed, and whitch speed and angle value is set, we send a speed and dircetion value to the broker
function move(spd, dir) {
  console.log(dir, spd);
  client.publish("seb/spd", String(spd));
  client.publish("seb/dir", String(dir));
}

/*onMounted(() => {
  client.on("connect", () => {
    console.log("Conntected!");
    client.subscribe("topic", function (err) {
      if (!err) {
        let info = JSON.stringify({
          user: "salle",
          message: "Hello mqtt",
        });
        client.publish("topic", info);
      }
    });
  });
});

client.on("message", (topic, message) => {
  console.log(`${topic} - ${message.toString()}`);
  let info = JSON.parse(message);
  chatMessages.value.push(info);
});

const publishMessage = ref("");
const chatMessages = ref([]);

const publish = () => {
  let info = JSON.stringify({
    user: "salle",
    message: publishMessage.value,
  });
  client.publish("topic", info);
  publishMessage.value = "";
};

*/
</script>

<style>
.container {
  background-color: rgb(9, 64, 78);
}
.arrow-up {
  transform: rotate(-90deg);
}
.arrow-down {
  transform: rotate(90deg);
}

.arrow-up-left {
  transform: rotate(-135deg);
}
.arrow-up-right {
  transform: rotate(-45deg);
}

.arrow-down-left {
  transform: rotate(135deg);
}
.arrow-down-right {
  transform: rotate(45deg);
}
.arrow-left {
  transform: rotate(180deg);
}

.sideInfo {
  width: 20%;
}

.scroll {
  background-color: rgb(12, 79, 95);
  border-radius: 20px;
  border: 1px solid;
}

.btn {
  border-radius: 100%;
  background-image: url("..//../public/icons/arrow.png");
  background-size: contain;
  box-shadow: 5px, 5px, 5px;
}
</style>
