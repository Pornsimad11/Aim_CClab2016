var rotate = document.getElementsByTagName( "DIV" )[0];

rotate.addEventListener( 'mouseover', function () {

    this.className = 'over';

}, false );

rotate.addEventListener( 'mouseout', function () {

    var rotate = this;

    rotate.className = 'out';
    window.setTimeout( function () { rotate.className = '' }, 5000, loop);

}, false );