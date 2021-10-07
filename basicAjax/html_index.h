const char html_index[] PROGMEM = R"(
<html>
<body>
  <p>Light: <label id='lbl_lit'></label></p>
  <p>Button: <label id='lbl_but'></label></p>
  <p>LED: <label id='lbl_led'></label></p>
  <script>
  function w(s) {document.write(s);}
  function id(s){return document.getElementById(s);}
  function loadValues() {
    var xhr=new XMLHttpRequest();
    xhr.onreadystatechange=function() {
      if(xhr.readyState==4 && xhr.status==200) {
        var jd=JSON.parse(xhr.responseText);
        id('lbl_lit').innerHTML=jd.light;
        id('lbl_but').innerHTML=(jd.button)?'pressed':'released';
        id('lbl_led').innerHTML=jd.led;
      }
    };
    xhr.open('GET','js',true);
    xhr.send();
  }
  setInterval(loadValues, 1000);
  </script>
</body>
</html>
)";
