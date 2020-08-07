
class JapanLamp {
	constructor(){
		this.dom = {};
		
		this._initColor();
		this._initWebSocket();
	}
	_initColor(){
		this.dom.colorbox = document.getElementById('colorPicker');
		let d = 600 * .35;
		this.colorWheel = new ReinventedColorWheel({
			appendTo: this.dom.colorbox,
			wheelReflectsSaturation: false,
			wheelThickness: d * .2,
			wheelDiameter: d,
			handleDiameter: d * .2 * .5,
			onChange: this.changeColor.bind(this)
		});
	}
	_initWebSocket(){
		this.wSocket = new WebSocket('ws://'+window.location.host+':81');
		// this.wSocket.onopen = function(e){ infobox.innerHTML = 'connected'; infobox.style.color = 'green'; }
		// this.wSocket.onclose = function(e){ infobox.innerHTML = 'disconnected'; infobox.style.color = 'black'; }
		// this.wSocket.onerror = function(e){ infobox.innerHTML = 'error'; infobox.style.color = 'red'; }
		this.wSocket.onmessage = this.socketMsg.bind(this);
	}

	changeColor(color){
		var r=parseInt("0x" +color.hex[1]+color.hex[2]);
		var g=parseInt("0x" +color.hex[3]+color.hex[4]);
		var b=parseInt("0x" +color.hex[5]+color.hex[6]);

		var rgb565 = (((r & 0xf8)<<8)+((g & 0xfc)<<3)+((b & 0xf8)>>3)).toString(16);
		while (rgb565.length<4){ rgb565 = "0" + rgb565; }
		
		document.body.style.backgroundColor = color.hex;
		// document.body.style.backgroundColor = '#'+rgb565;
		console.log('#'+rgb565, ' - color');
	}

	socketMsg(e){
		console.log(e, arguments);
	}
};
