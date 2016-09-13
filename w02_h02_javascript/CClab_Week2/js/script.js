var costumes = ["costume1", "costume2", "costume3", "costume4", "costume5" ]; // name of image files for costume
var text = ["text1", "text2", "text3", "text4", "text5" ]; // name of image files for costume

var randomCostumes = 0; 
var randomCostume_description = 0;

$(document).ready(function(){
    init();
});

function init(){
    console.log("Pickacostume");
    $('#submit').click(function(){
    showCostume();
    })

};

function showCostume(){
    // randomCostumes_description = randomNumGenerator(text);
    randomCostumes = randomNumGenerator(costumes);
    $('#costume-picker').css("background","url('images/"+costumes[randomCostumes]+".png') no-repeat");
    $('#costume-picker').css("background-position", "center");
    $('#costume-picker').css("top","300px;");
    $('#costume-picker').css("animation-iteration-count","0");
    $('#submit').css("background","url('images/"+text[randomCostumes]+".png') no-repeat, #FCF8CC");
    $('#submit').css("background-position", "center");

}

function randomNumGenerator(arrayName){
    return Math.floor(Math.random()*arrayName.length);
};