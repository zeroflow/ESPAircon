<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <!-- The above 3 meta tags *must* come first in the head; any other head content must come *after* these tags -->
    <title>Airconditioning</title>
    <link rel="shortcut icon" href="resources/favicon.png">
    <!-- Bootstrap -->
    <link href="css/bootstrap.min.css" rel="stylesheet">
    <!-- Style -->
    <link href="css/bootstrap-theme.min.css" rel="stylesheet">

    <!-- HTML5 shim and Respond.js for IE8 support of HTML5 elements and media queries -->
    <!-- WARNING: Respond.js doesn't work if you view the page via file:// -->
    <!--[if lt IE 9]>
      <script src="https://oss.maxcdn.com/html5shiv/3.7.2/html5shiv.min.js"></script>
      <script src="https://oss.maxcdn.com/respond/1.4.2/respond.min.js"></script>
    <![endif]-->
  </head>
  <body role="document">
  
    <div class="container theme-showcase" role="main">


      <div class="page-header">
            <h1> <span class="glyphicon glyphicon-home" aria-hidden="true"></span> Airconditioning</h1>
      </div>
      
      
      <div class="row">
        <div class="col-sm-4">
                <form action="/aircon/set" method="post">
                
                <div class="input-group">
                  <span class="input-group-addon">
                    <input type="checkbox" name="on" aria-label="..." {{ "checked" if data["on"] == True else "" }}>
                    Temperature
                  </span>
                  <input type="number" name="temperature" class="form-control" aria-label="..." value="{{ data["temperature"] }}">
                </div><!-- /input-group -->
                
                <div class="col-sm-12">
                    <div class="col-sm-3">
                        <p><h3>Mode</h3></p>
                    </div>
                    
                    <div class="col-sm-9">
                        <div class="radio">
                          <label>
                            <input type="radio" name="mode" id="mode" value="8" {{ "checked" if data["mode"] == 8 else "" }}>
                            Airconditioning
                          </label>
                        </div>
                        <div class="radio">
                          <label>
                            <input type="radio" name="mode" id="mode" value="2" {{ "checked" if data["mode"] == 2 else "" }}>
                            Dehumidify
                          </label>
                        </div>
                        <div class="radio disabled">
                          <label>
                            <input type="radio" name="mode" id="mode" value="1" {{ "checked" if data["mode"] == 1 else "" }}>
                            Fan
                          </label>
                        </div>
                    </div>
                </div>
                
                <div class="col-sm-12">
                    <div class="col-sm-3">
                        <p><h3>Fan</h3></p>
                    </div>
                    
                    <div class="col-sm-9">
                        <div class="radio">
                          <label>
                            <input type="radio" name="fan" id="fan" value="1" {{ "checked" if data["fan"] == 1 else "" }}>
                            High
                          </label>
                        </div>
                        <div class="radio">
                          <label>
                            <input type="radio" name="fan" id="fan" value="2" {{ "checked" if data["fan"] == 2 else "" }}>
                            Medium
                          </label>
                        </div>
                        <div class="radio disabled">
                          <label>
                            <input type="radio" name="fan" id="fan" value="4" {{ "checked" if data["fan"] == 4 else "" }}>
                            Low
                          </label>
                        </div>
                    </div>
                </div>
                
                <div class="input-group">
                  <span class="input-group-addon">
                    <input type="checkbox" name="timer" aria-label="..." {{ "checked" if data["timer"] else "" }}>
                    Timer
                  </span>
                  <input type="number" name="timer_value" class="form-control" aria-label="..." value="{{ data["timer_value"] }}">
                </div><!-- /input-group -->
                
                    <div class="form-group">
                        <div class="btn-group btn-group-justified" role="group" aria-label="...">
                          <div class="btn-group" role="group">  
                            <button type="submit" class="btn btn-default">Send</button>
                          </div>
                        </div>
                    </div>
              </form>
                
        </div>
      </div>
      
      
    </div>
  
    <!-- Include all compiled plugins (below), or include individual files as needed -->
    <script src="js/bootstrap.min.js"></script>
  </body>
</html>