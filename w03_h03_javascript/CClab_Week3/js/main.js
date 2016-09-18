//https://codepen.io/mguthrie/pen/oxzYOK

!function(){ //!makes function runs immediately 
  
  var getGiphy = {
    
    url: "https://api.giphy.com/v1/stickers/random?api_key=dc6zaTOxFJmzC&tag=scary",
    
    writeToHTML: function(url, alt) { //building the url to go get data
      var imgHTML = '<img class="img-responsive" src="';
      imgHTML += url;
      imgHTML += '" alt="'
      imgHTML += alt;
      imgHTML += '">';
      return imgHTML;
    }
    
  }
  
  function callJSON(url) {
    
    $.getJSON(url, function(response){
      var newHTML = getGiphy.writeToHTML(response.data.image_url, response.data.caption);//get the response data from Giphy
      $('#view').html(newHTML);//put into view div
    });
    
  }
  
  function newGiphy(el) {
      callJSON(getGiphy.url);//getting new Giphy
      return true;
    }
    
  callJSON(getGiphy.url);//happens when click
    
  $("#search-button").on('click', function(){
    newGiphy('#view');
  });
    
}();



