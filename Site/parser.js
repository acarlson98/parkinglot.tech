function currentConditions(){

    var URL = "http://dataservice.accuweather.com/currentconditions/v1/2231320?apikey=riUagffR7Gc4oIG8JYW6y0CDJXxINaCV";
    
    fetch(URL)
    .then((response) => {
        return response.json();
    })
    .then((myJson) => {
        console.log(myJson);
        // var myObj = JSON.parse(myJson);
        document.getElementById("demo").innerHTML = myJson[0].WeatherText;
        document.getElementById("demo2").innerHTML = myJson[0].Temperature.Imperial.Value + myJson[0].Temperature.Imperial.Unit;
    });

//   var myObj = JSON.parse(json);
//   document.getElementById("demo").innerHTML = myObj[0].LocalObservationDateTime;
}