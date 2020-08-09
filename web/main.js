var ge = document.getElementById.bind(document);

var JapanLamp = function() {
  this.dom = {};

  // this.color = "#FF0000";
  this.color = [255, 0, 0];
  this.brightness = 140;
  this.wSocket = null;

  this._initColor();
  this._initBrightness();
  this._initWebSocket();
};

JapanLamp.prototype = {
  _msg: function() {
    // return `c_${this.color}-b_${this.brightness}`;
    var msg = "c_r" + this.color[0] + "g" + this.color[1] + "b" + this.color[2];
    msg += "-b_" + this.brightness;
    return msg;
  },
  sendMsg: function() {
    if (this.wSocket) {
      this.wSocket.send(this._msg());
    }
  },
  _initColor: function() {
    this.dom.colorPicker = ge("colorPicker");
    this.dom.color = ge("color");

    var d = 600 * 0.35;
    this.colorWheel = new ReinventedColorWheel({
      appendTo: this.dom.colorPicker,
      wheelReflectsSaturation: false,
      wheelThickness: d * 0.2,
      wheelDiameter: d,
      handleDiameter: d * 0.2 * 0.5,
      rgb: this.color,
      onChange: this.changeColor.bind(this),
    });
    this.dom.color.style.backgroundColor = this.color;
  },
  _initBrightness: function() {
    this.dom.brightnessInput = ge("brightnessInput");
    this.dom.brightnessBox = ge("brightnessBox");

    this.dom.brightnessInput.value = this.brightness;
    this.dom.brightnessInput.addEventListener(
      "input",
      this.changeBrightness.bind(this)
    );
    this.changeBrightness({ target: this.dom.brightnessInput });
  },
  _initWebSocket: function() {
    this.wSocket = new WebSocket("ws://" + window.location.host + ":81");
    this.wSocket.onopen = function(e) {
      console.log("connected");
    };
    this.wSocket.onclose = function(e) {
      console.log("disconnected");
    };
    this.wSocket.onerror = function(e) {
      console.log("error");
    };
    this.wSocket.onmessage = this.socketMsg.bind(this);
  },

  changeColor: function(color) {
    var r = parseInt("0x" + color.hex[1] + color.hex[2]);
    var g = parseInt("0x" + color.hex[3] + color.hex[4]);
    var b = parseInt("0x" + color.hex[5] + color.hex[6]);

    var rgb565 = (
      ((r & 0xf8) << 8) +
      ((g & 0xfc) << 3) +
      ((b & 0xf8) >> 3)
    ).toString(16);
    while (rgb565.length < 4) {
      rgb565 = "0" + rgb565;
    }

    this.dom.color.style.backgroundColor = color.hex;
    console.log("#" + rgb565, " - color");
    this.sendMsg();
  },
  changeBrightness: function(e) {
    var v = e.target.value;
    this.dom.brightnessBox.style.backgroundColor =
      "rgb(" + v + "," + v + "," + v + ")";
    console.log(e.target.value, "brightness input value");
    this.sendMsg();
  },
  socketMsg: function(e) {
    console.log(e.data);
  },
};
