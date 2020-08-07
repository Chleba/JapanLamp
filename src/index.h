const char HTML_INDEX[] PROGMEM = R"=====(
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd"><html xmlns="http://www.w3.org/1999/xhtml" lang="en" xml:lang="en"><head><meta http-equiv="Content-Type" content="text/html; charset=utf-8" /><meta name="viewport" content="width=device-width, initial-scale=0.05"><title>Japan Lamp Control</title><style type="text/css" media="screen">/*<![CDATA[*/body{height:100vh;padding:0;margin:0}#colorPicker{height:100%;display:flex;justify-content:center;align-items:center}.reinvented-color-wheel,.reinvented-color-wheel--hue-handle,.reinvented-color-wheel--hue-wheel,.reinvented-color-wheel--sv-handle,.reinvented-color-wheel--sv-space{touch-action:manipulation;touch-action:none;-webkit-touch-callout:none;-webkit-tap-highlight-color:transparent;-webkit-user-select:none;-moz-user-select:none;-ms-user-select:none;user-select:none}.reinvented-color-wheel{position:relative;display:inline-block;line-height:0;border-radius:50%}.reinvented-color-wheel--hue-wheel{border-radius:50%}.reinvented-color-wheel--sv-space{position:absolute;left:0;top:0;right:0;bottom:0;margin:auto}.reinvented-color-wheel--hue-handle,.reinvented-color-wheel--sv-handle{position:absolute;box-sizing:border-box;border-radius:50%;border:2px solid #fff;box-shadow:0 0 0 1px #000 inset}.reinvented-color-wheel--hue-handle{pointer-events:none}/*]]>*/</style> <script charset="utf-8">/*<![CDATA[*/var ReinventedColorWheel=function(){"use strict" var e=function(e){var t=e[0],n=e[1]/100,h=e[2]/100 return 0===h?[0,0,0]:[t,2*(n*=(h*=2)<=1?h:2-h)/(h+n)*100,(h+n)/2*100]},t=function(e){var t,n,h=e[0],i=e[1]/100,r=e[2]/100 return t=i*r,[h,100*(t=(t/=(n=(2-i)*r)<=1?n:2-n)||0),100*(n/=2)]} function n(e){var t=e[0],n=e[1],h=e[2],i=Math.max(t,n,h),r=i-Math.min(t,n,h),s=r&&60*(i===t?(n-h)/r%6:i===n?(h-t)/r+2:(t-n)/r+4) return[s<0?s+360:s,i&&100*r/i,100*i/255]}function h(e){var t=e[0]/60,n=e[1]/100,h=e[2]/100,i=h*n,r=h-i,s=255*(i*(1-Math.abs(t%2-1))+r)+.5|0,o=255*(i+r)+.5|0,a=255*r+.5|0,l=0|t return 1===l?[s,o,a]:2===l?[a,o,s]:3===l?[a,s,o]:4===l?[s,a,o]:5===l?[o,a,s]:[o,s,a]}function i(e){var t,n=Math.round((t=e,0,255,Math.min(Math.max(t,0),255))).toString(16) return 1==n.length?"0"+n:n}var r=function(e){var t=4===e.length?i(255*e[3]):"" return"#"+i(e[0])+i(e[1])+i(e[2])+t},s=function(e){4!==e.length&&5!==e.length||(e=function(e){for(var t="#",n=1;n<e.length;n++){var h=e.charAt(n) t+=h+h}return t}(e)) var t=[parseInt(e.substring(1,3),16),parseInt(e.substring(3,5),16),parseInt(e.substring(5,7),16)] if(9===e.length){var n=parseFloat((parseInt(e.substring(7,9),16)/255).toFixed(2)) t.push(n)}return t} function o(e,t){return e?[c(e[0])?l(e[0]):t[0],c(e[1])?u(e[1]):t[1],c(e[2])?u(e[2]):t[2]]:t}function a(e){return[l(e[0]),u(e[1]),u(e[2])]}function l(e){var t=Math.round(e%360*10)/10 return t<0?t+360:t}function u(e){return e<0?0:e>100?100:(10*e+.5|0)/10}function c(e){return"number"==typeof e&&isFinite(e)}var v="PointerEvent"in window?function(e,t,n){e.addEventListener("pointerdown",(function(e){0===e.button&&!1!==t(e)&&this.setPointerCapture(e.pointerId)})),e.addEventListener("pointermove",(function(e){this.hasPointerCapture(e.pointerId)&&n(e)}))}:"ontouchend"in window?function(e,t,n){var h=!1 e.addEventListener("touchstart",(function(e){1===e.touches.length&&!1!==t(e.touches[0])&&(h=!0,e.preventDefault())})),e.addEventListener("touchmove",(function(e){h&&1===e.touches.length&&(e.preventDefault(),n(e.touches[0]))}))}:function(e,t,n){var h=function(e){n(e)},i=function(){removeEventListener("mouseup",i),removeEventListener("mousemove",h)} e.addEventListener("mousedown",(function(e){0===e.button&&!1!==t(e)&&(addEventListener("mousemove",h),addEventListener("mouseup",i))}))},d={hsv:[0,100,100],hsl:[0,100,50],wheelDiameter:200,wheelThickness:20,handleDiameter:16,wheelReflectsSaturation:!0,onChange:function(){}},p=window.DOMMatrix||window.WebKitCSSMatrix||window.MSCSSMatrix function f(e,t){var n=document.createElement(e) return n.className=t,n}return(function(){function i(e){var t=this this.options=e,this.wheelDiameter=this.options.wheelDiameter||d.wheelDiameter,this.wheelThickness=this.options.wheelThickness||d.wheelThickness,this.handleDiameter=this.options.handleDiameter||d.handleDiameter,this.onChange=this.options.onChange||d.onChange,this.wheelReflectsSaturation=void 0!==this.options.wheelReflectsSaturation?this.options.wheelReflectsSaturation:d.wheelReflectsSaturation,this.rootElement=this.options.appendTo.appendChild(f("div","reinvented-color-wheel")),this.hueWheelElement=this.rootElement.appendChild(f("canvas","reinvented-color-wheel--hue-wheel")),this.hueWheelContext=this.hueWheelElement.getContext("2d"),this.hueHandleElement=this.rootElement.appendChild(f("div","reinvented-color-wheel--hue-handle")),this.svSpaceElement=this.rootElement.appendChild(f("canvas","reinvented-color-wheel--sv-space")),this.svSpaceContext=this.svSpaceElement.getContext("2d"),this.svHandleElement=this.rootElement.appendChild(f("div","reinvented-color-wheel--sv-handle")),this._redrawHueWheel=function(){t._redrawHueWheelRequested=!1 var e=t.wheelDiameter,n=e/2,h=n-t.wheelThickness/2,i=Math.PI/180,r=t.wheelReflectsSaturation?","+t._hsl[1]+"%,"+t._hsl[2]+"%)":",100%,50%)",s=t.hueWheelContext s.clearRect(0,0,e,e),s.lineWidth=t.wheelThickness for(var o=0;o<360;o++)s.beginPath(),s.arc(n,n,h,(o-90.7)*i,(o-89.3)*i),s.strokeStyle="hsl("+o+r,s.stroke()},this.hueWheelContext.imageSmoothingEnabled=!1,this.svSpaceContext.imageSmoothingEnabled=!1,this._hsv=o(e.hsv?e.hsv:e.hsl?i.hsl2hsv(e.hsl):e.rgb?i.rgb2hsv(e.rgb):e.hex?i.rgb2hsv(i.hex2rgb(e.hex)):void 0,d.hsv),this._hsl=a(i.hsv2hsl(this._hsv)),this._rgb=i.hsv2rgb(this._hsv),this._hex=i.rgb2hex(this._rgb) var n=function(e,n){var h=t._inverseTransform.multiply(new p("matrix(1,0,0,1,"+e+","+n+")")) return{x:h.e,y:h.f}},h=function(e){t._inverseTransform=function(e){for(var t=[e];e=e.parentElement;)t.push(e) for(var n=new p,h=t.length-1;h>=0;h--){var i=getComputedStyle(t[h]),r=i.transform if(r&&"none"!==r){var s=i.transformOrigin.split(" ").map(parseFloat) n=n.translate(s[0],s[1]).multiply(new p(r)).translate(-s[0],-s[1])}}return n.inverse()}(e) var h=e.getBoundingClientRect() t._center=n(h.left+h.width/2,h.top+h.height/2)},r=function(e){var h=n(e.clientX,e.clientY),i=h.x-t._center.x,r=h.y-t._center.y,s=Math.atan2(r,i) t.hsv=[180*s/Math.PI+90,t.hsv[1],t.hsv[2]]},s=function(e){var h=n(e.clientX,e.clientY),i=100/t.svSpaceElement.width,r=(h.x-t._center.x)*i+50,s=(t._center.y-h.y)*i+50 t.hsv=[t._hsv[0],r,s]},l=function(e){h(t.svSpaceElement),s(e)} v(this.hueWheelElement,(function(e){h(t.hueWheelElement) var i=n(e.clientX,e.clientY),s=i.x-t._center.x,o=i.y-t._center.y,a=t.wheelDiameter/2-t.wheelThickness if(s*s+o*o<a*a)return!1 r(e)}),r),v(this.svSpaceElement,l,s),v(this.svHandleElement,l,s),this.redraw()}return Object.defineProperty(i.prototype,"hsv",{get:function(){return this._hsv},set:function(e){this._setHSV(e)},enumerable:!0,configurable:!0}),Object.defineProperty(i.prototype,"hsl",{get:function(){return this._hsl},set:function(e){this._setHSV(i.hsl2hsv(e))},enumerable:!0,configurable:!0}),Object.defineProperty(i.prototype,"rgb",{get:function(){return this._rgb},set:function(e){this._setHSV(i.rgb2hsv(e))},enumerable:!0,configurable:!0}),Object.defineProperty(i.prototype,"hex",{get:function(){return this._hex},set:function(e){this.rgb=i.hex2rgb(e)},enumerable:!0,configurable:!0}),i.prototype.setHSV=function(){this.hsv=arguments},i.prototype.setHSL=function(){this.hsl=arguments},i.prototype.redraw=function(){this.hueWheelElement.width=this.hueWheelElement.height=this.wheelDiameter,this.svSpaceElement.width=this.svSpaceElement.height=(this.wheelDiameter-2*this.wheelThickness)*Math.SQRT1_2 var e=this.hueHandleElement.style,t=this.svHandleElement.style e.width=e.height=t.width=t.height=this.handleDiameter+"px",e.marginLeft=e.marginTop=t.marginLeft=t.marginTop=-this.handleDiameter/2+"px",this._redrawHueWheel(),this._redrawHueHandle(),this._redrawSvSpace(),this._redrawSvHandle()},i.prototype._setHSV=function(e){var t=this._hsv,n=this._hsv=o(e,t),h=t[0]-n[0],r=t[1]-n[1]||t[2]-n[2] h&&(this._hsl=[n[0],this._hsl[1],this._hsl[2]],this._redrawHueHandle(),this._updateSvBackground()),r&&(this._hsl=a(i.hsv2hsl(n)),this._redrawSvHandle(),this.wheelReflectsSaturation&&!this._redrawHueWheelRequested&&(requestAnimationFrame(this._redrawHueWheel),this._redrawHueWheelRequested=!0)),(h||r)&&(this._rgb=i.hsv2rgb(n),this._hex=i.rgb2hex(this._rgb),this.onChange(this))},i.prototype._redrawSvSpace=function(){this._updateSvBackground() var e=this.svSpaceElement.width,t=this.svSpaceContext,n=t.createLinearGradient(0,0,e,0),h=t.createLinearGradient(0,0,0,e) n.addColorStop(0,"rgba(255,255,255,1)"),n.addColorStop(1,"rgba(255,255,255,0)"),h.addColorStop(0,"rgba(0,0,0,0)"),h.addColorStop(1,"rgba(0,0,0,1)"),t.fillStyle=n,t.fillRect(0,0,e,e),t.fillStyle=h,t.fillRect(0,0,e,e)},i.prototype._updateSvBackground=function(){this.svSpaceElement.style.backgroundColor="hsl("+this._hsv[0]+",100%,50%)"},i.prototype._redrawHueHandle=function(){var e=this.wheelDiameter/2,t=e-this.wheelThickness/2,n=(this._hsv[0]-90)*Math.PI/180,h=this.hueHandleElement.style h.left=t*Math.cos(n)+e+"px",h.top=t*Math.sin(n)+e+"px"},i.prototype._redrawSvHandle=function(){var e=this.svSpaceElement,t=this.svHandleElement.style t.left=e.offsetLeft+e.offsetWidth*this._hsv[1]/100+"px",t.top=e.offsetTop+e.offsetHeight*(1-this._hsv[2]/100)+"px"},i.default=i,i.defaultOptions=d,i.hsv2hsl=t,i.hsl2hsv=e,i.hsv2rgb=h,i.rgb2hsv=n,i.rgb2hex=r,i.hex2rgb=s,i}())}()/*]]>*/</script> </head><body><div id="colorPicker"></div> <script charset="utf-8">var changeColor=function(color){console.log(color.rgb);};let d=window.innerWidth*.25;var colorWheel=new ReinventedColorWheel({appendTo:document.getElementById('colorPicker'),wheelReflectsSaturation:false,wheelThickness:d*.2,wheelDiameter:d,handleDiameter:d*.2*.5,onChange:changeColor});</script> </body></html>
)=====";
