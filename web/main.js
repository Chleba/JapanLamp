
var ge = document.getElementById.bind(document);

class JapanLamp {
	constructor(){
		this.dom = {};
		
		this.color = '#FF0000';
		this.brightness = 140;
		this.wSocket = null;

		this._initColor();
		this._initBrightness();
		this._initWebSocket();
	}
	_msg(){ return `c_${this.color}-b_${this.brightness}`; }
	sendMsg(){
		if(this.wSocket){
			this.wSocket.send(this._msg());
		}
	}
	_initColor(){
		this.dom.colorPicker = ge('colorPicker');
		this.dom.color = ge('color');

		let d = 600 * .35;
		this.colorWheel = new ReinventedColorWheel({
			appendTo: this.dom.colorPicker,
			wheelReflectsSaturation: false,
			wheelThickness: d * .2,
			wheelDiameter: d,
			handleDiameter: d * .2 * .5,
			hex: this.color,
			onChange: this.changeColor.bind(this)
		});
		this.dom.color.style.backgroundColor = this.color;
	}
	_initBrightness(){
		this.dom.brightnessInput = ge('brightnessInput');
		this.dom.brightnessBox = ge('brightnessBox');

		this.dom.brightnessInput.value = this.brightness;
		this.dom.brightnessInput.addEventListener('input', this.changeBrightness.bind(this));
		this.changeBrightness({target:this.dom.brightnessInput});
	}
	_initWebSocket(){
		this.wSocket = new WebSocket('ws://'+window.location.host+':81');
		this.wSocket.onopen = function(e){ console.log('connected'); }
		this.wSocket.onclose = function(e){ console.log('disconnected'); }
		this.wSocket.onerror = function(e){ console.log('error'); }
		this.wSocket.onmessage = this.socketMsg.bind(this);
	}

	changeColor(color){
		var r=parseInt("0x" +color.hex[1]+color.hex[2]);
		var g=parseInt("0x" +color.hex[3]+color.hex[4]);
		var b=parseInt("0x" +color.hex[5]+color.hex[6]);

		var rgb565 = (((r & 0xf8)<<8)+((g & 0xfc)<<3)+((b & 0xf8)>>3)).toString(16);
		while (rgb565.length<4){ rgb565 = "0" + rgb565; }
		
		this.dom.color.style.backgroundColor = color.hex;
		console.log('#'+rgb565, ' - color');
		this.sendMsg();
	}
	changeBrightness(e){
		var v = e.target.value;
		this.dom.brightnessBox.style.backgroundColor = 'rgb('+v+','+v+','+v+')';
		console.log(e.target.value, 'brightness input value');
		this.sendMsg();
	}
	socketMsg(e){
		console.log(e.data);

	}
};
