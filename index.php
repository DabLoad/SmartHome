<!DOCTYPE html>
<html >
<head>
  <meta charset="UTF-8">
  <title>Sliding Page</title>
  <link rel="stylesheet" href="css/reset.css">
  <link rel="stylesheet" href="css/style.css">
  <link rel="stylesheet" href="css/menu.css">
  <link rel="stylesheet" href="js/c3-0.6.6/c3.css">
</head>

<body>
  <!-- button -->
<div class="button">
  <span class="line"></span>
  <span class="line"></span>
  <span class="line"></span>
</div>
<!-- navbar menu -->
<div class='menu'>
  <nav>
    <ul>
      <li>
        <a href='#' data-class='home_is_visible '>Home</a>
      </li>
      <li>
        <a href='#' data-class='energy_is_visible'>Energy</a>
      </li>
      <li>
        <a href='#' data-class='debug_is_visible'>debug</a>
      </li>
    </ul>
  </nav>
</div>

<!-- content -->
<div class="content">
<div class='content home'>
  <div class='content-header'>
  <h1>OffCanvas Nav</h1>
  </div> 
    <p><?php echo date("Y-m-d-s");?></p>
  </div>
<div class='content energy'>
  <div class='content-header'>
    <h1>SDM220</h1>
  </div>
  <div id="chart" style="width: 70%;min-width: 400px;height: 300px;"></div><br>

</div>
<div class='content debug'>
  <div class='content-header'>
    <h1>debug</h1>
  </div>
  <div>
    <a href="/modules/SDM220/SDM220.php">/modules/SDM220/SDM220.php</a><br>
    <span>Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod
    tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam,
    quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo
    consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse
    cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non
    proident, sunt in culpa qui officia deserunt mollit anim id est laborum.</span>
  </div>
</div>
  <script type="text/javascript" src='js/jquery-3.3.1.min.js'></script>
  <script  src="js/d3/d3.min.js"></script>
  <script  src="js/c3-0.6.6/c3.min.js"></script>
  <script  src="js/index.js"></script>
</div>
</body>
<footer></footer>
</html>
