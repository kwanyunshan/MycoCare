fetch("http://192.168.0.101/data")

.then(response=>response.json())

.then(data=>{

document.getElementById("temp").innerHTML=data.temperature;

});