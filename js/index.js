$(document).ready(function () {
$(function(){
  /*--------- show and hide the menu  ---*/
  $('.button').on("click", function(){
    if($('body').hasClass('nav_is_visible') == true){
     $('body').removeClass('nav_is_visible');
     $('.button').removeClass('close');
        }
    else{
     $('body').addClass('nav_is_visible');
     $('.button').addClass('close');
       }
   });
  
  $('body').addClass('home_is_visible');

    
 function removeClasses() {
  $(".menu ul li").each(function() {
    var custom_class = $(this).find('a').data('class');
  $('body').removeClass(custom_class);
  });
}
  
  $('.menu a').on('click',function(e){
    e.preventDefault();
    removeClasses();
    var custom_class = $(this).data('class');
    $('body').addClass(custom_class);
  });
});


function Queue() {
  this.data = [];
}

Queue.prototype.at = function(id) {
  return this.data[id];
}

Queue.prototype.add = function(record) {
  this.data.unshift(record);
}

Queue.prototype.remove = function() {
  this.data.pop();
}

Queue.prototype.first = function() {
  return this.data[0];
}

Queue.prototype.last = function() {
  return this.data[this.data.length - 1];
}

Queue.prototype.size = function() {
  return this.data.length;
}

const q = new Queue();


for (var i = 0; i < 10; i++) {
  q.add(null);
}
var chart = c3.generate({
    bindto: '#chart',
    data: {
      columns: [
        ['data1', null]
       //['data2', null]
      ],
      axes: {
        data2: 'y2'
      }
    },
    axis: {
      y: {
        label: { // ADD
          text: 'Y Label',
          position: 'outer-middle'
        }
      },
      y2: {
        show: true,
        label: { // ADD
          text: 'Y2 Label',
          position: 'outer-middle'
        }
      }
    }
});

setInterval(function() {
  q.remove;
  q.add((Math.random() * 10).toFixed(0));
  chart.load({
        rows: [
            ['data1'],
            [q.at(9)],
            [q.at(8)],
            [q.at(7)],
            [q.at(6)],
            [q.at(5)],
            [q.at(4)],
            [q.at(3)],
            [q.at(2)],
            [q.at(1)],
            [q.at(0)]
        ]
  });
  
}, 1000);

    $('.content .energy').append('<div id="SDM220"></div>');
    $('#SDM220').load("/modules/SDM220/SDM220.php");
});