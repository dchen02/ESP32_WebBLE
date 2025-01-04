let nIntervId;
var ledr=0;
var ledg=0;
var ledb=0;


(function($){
  
  
    
	var initLayout = function() {
        

		
		$('#colorpickerHolder').ColorPicker({ flat: true, onChange: function (hsb, hex, rgb) { 

      if (ledr!=rgb.r && ledg!=rgb.g && ledb!=rgb.b){
        nusSendString(rgb.r+","+rgb.g+","+rgb.b);

      }


               ledr=rgb.r;
               ledg=rgb.g;
               ledb=rgb.b;
           }
     });
		
        
	
	
	};
	
	
	
	EYE.register(initLayout, 'init');
    
    
  
    

    

    
})(jQuery)




   
///////////////// SERIAL

/*
  let lineBuffer = '';
      let latestValue = 0;
	
	var x;
	var y;
	var z;
	var ar="on";
	
	
	var normalx;
	var normaly;
	
	var prex;
		var prey;
	var valid;
	
 let split_data;
    
      function renderDemo() {
        //const percentage = Math.floor(latestValue / 1023 * 100);
        const msg = document.getElementById('output');
        msg.innerText = latestValue;
        window.requestAnimationFrame(renderDemo);
      }
      
      
      window.requestAnimationFrame(renderDemo);


async function getReader() {
        port = await navigator.serial.requestPort({});
        await port.open({ baudRate: 115200 });

        connectButton.innerText = '🔌 Disconnect';

        const appendStream = new WritableStream({
          write(chunk) {

			   lineBuffer += chunk;
			  var lines= lineBuffer.split('\n');
			  
			  while(lines.length > 1) {
				  		var message=lines.shift();
						//console.log(message);
                  split_data = message.split("|");
			  }
			  
			  lineBuffer = lines.pop();
			  

            latestValue=chunk;

          }
        });

        


                 

        port.readable
          .pipeThrough(new TextDecoderStream())
          .pipeTo(appendStream);
          
      }

 
 async function nusSendString(data) {
	encoder = new TextEncoder();
	const dataArrayBuffer = encoder.encode(data+"\n");


	if (port && port.writable) {

		const writer = port.writable.getWriter();
		writer.write(dataArrayBuffer);
		writer.releaseLock();

	}else{
        console.log("busy");
    }
}
 
 
 
 
    const connectButton = document.getElementById ('connect-button');
   
    
let port;







if ('serial' in navigator) {
  connectButton.addEventListener('click', function () {
    if (port) {
      port.close();
      port = undefined;

      connectButton.innerText = 'Connect';
      document.querySelector('figure').classList.replace('bounceIn', 'fadeOut');
    }
    else {
      getReader();
    }
  });

  connectButton.disabled = false;
}
else {
  const firstBubble = document.querySelector('p.bubble');
  const noSerialSupportNotice = document.createElement('p');
  noSerialSupportNotice.innerHTML = '<p class="notice bubble">You\'re on the right track! This browser is lacking support for Web Serial API, though, and thats a bummer.</p>';
  firstBubble.parentNode.insertBefore(noSerialSupportNotice, firstBubble.nextSibling);
}


*/