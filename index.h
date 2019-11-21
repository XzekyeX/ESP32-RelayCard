const char webpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
    <head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
    <title>Relay I/O Module by FIMiTek</title>
    <style>
        .btn_on {
            box-shadow:inset 0px 1px 0px 0px #9acc85;
            background:linear-gradient(to bottom, #74ad5a 5%, #68a54b 100%);
            background-color:#74ad5a;
            border:1px solid #3b6e22;
            display:inline-block;
            cursor:pointer;
            color:#ffffff;
            font-family:Courier New;
            font-size:15px;
            font-weight:bold;
            padding:16px 16px;
            text-decoration:none;
        }
        .btn_on:hover {
            background:linear-gradient(to bottom, #68a54b 5%, #74ad5a 100%);
            background-color:#68a54b;
        }
        .btn_on:active {
            position:relative;
            top:1px;
        }
        
        .btn_off {
            box-shadow:inset 0px 1px 0px 0px #d63232;
            background:linear-gradient(to bottom, #ff0000 5%, #c40f0f 100%);
            background-color:#ff0000;
            border:1px solid #6e2222;
            display:inline-block;
            cursor:pointer;
            color:#ffffff;
            font-family:Courier New;
            font-size:15px;
            font-weight:bold;
            padding:16px 16px;
            text-decoration:none;
        }
        .btn_off:hover {
            background:linear-gradient(to bottom, #c40f0f 5%, #ff0000 100%);
            background-color:#c40f0f;
        }
        .btn_off:active {
            position:relative;
            top:1px;
        }

        
    </style>
    </head>
    <body onload="init()"> 
        <div>
            <h1>Log: <span id="log"></span></h1>           
        </div>
        <div>
            <button id="io16" onclick="gpio(0,16)" class="btn_off" >Relay 0, GPIO 16</button>
            <button id="io17" onclick="gpio(1,17)" class="btn_off" >Relay 1, GPIO 17</button>
            <button id="io5" onclick="gpio(2,5)" class="btn_off" >Relay 2, GPIO 5</button>
            <button id="io18" onclick="gpio(3,18)" class="btn_off" >Relay 3, GPIO 18</button>
            <button id="io19" onclick="gpio(4,19)" class="btn_off" >Relay 4, GPIO 19</button>
            <button id="io21" onclick="gpio(5,21)" class="btn_off" >Relay 5, GPIO 21</button>
        </div> 
    </body>
    <script type="text/javascript">
        function init() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    var response = this.responseText;
                    var a = response.split(";");
                    if(a.length > 0) {
                        for(var i = 0; i < a.length; i++) {
                            var r = a[i].trim();
                            if(r.startsWith("io")){     
                                if(r.length > 3) {
                                    var v = r.substring(3,r.length - 1);
                                    var s = v.split(",");
                                    if(s.length > 1){
                                        var id = s[0].trim();
                                        var state = s[1].trim();
                                        document.getElementById("log").innerHTML = r;                                    
                                        changeBtnClass(id,state);
                                    }
                                }    
                            }
                        }
                    }
                }
            };
            xhttp.open("GET", "gpios", true);
            xhttp.send();
        }

        setInterval(function () {
            // Call a function repetatively with 5 Second interval
//            getServerResponse();
        }, 5000); //5000mSeconds update rate

        function getServerResponse() {
            var xhttp = new XMLHttpRequest();
            xhttp.open("GET", "", true);
            xhttp.send();
        }

        function changeBtnClass(id,state) {
            switch(state){
                case "0":
                    document.getElementById("io" + id).className = "btn_off";                                    
                    break;
                case "1":
                    document.getElementById("io" + id).className = "btn_on";   
                    break;
                default:
            }
        }

        function gpio(id,io) {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    var r = this.responseText;
                    if(r.startsWith("io")){     
                        if(r.length > 3) {
                            var v = r.substring(3,r.length - 1);
                            var s = v.split(",");
                            if(s.length > 1){
                                var id = s[0].trim();
                                var state = s[1].trim();
                                document.getElementById("log").innerHTML = r;                                    
                                changeBtnClass(id,state);
                            }
                        }        
                    }
                }
            };
            xhttp.open("GET", "gpio?io=" + io + "&id=" + id, true);
            xhttp.send();
        }

    </script>
</html>
)=====";