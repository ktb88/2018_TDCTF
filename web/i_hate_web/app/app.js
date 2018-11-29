/*
    2018 Tendollar CTF - WEB
    Node.JS HTTP Parser bug with LATIN-1
    Made by t0rchwo0d
*/

process.on('uncaughtException' , function (err) {
    console.error("[!] uncaughtException : " + err);
});

/////////////////////////////////////////////////
var flag = "TDCTF{nodejs_http_parer_bug_LATIN1}";
/////////////////////////////////////////////////

var http = require("http");
var url = require("url");
var querystring = require("querystring");

var responseError = function(response, data) {
    response.writeHead(400, {"Content-Type":"text/html"});
    response.write("<h3>What are you doing?</h3><br/>");
    response.write("<b>Your input : " + data + "</b><br/><br/>");
    response.end("");
}

var compareAddress = function(local, remote) {
    if (local == remote) {
        return true;
    } else {
        return false;
    }
}

var server = http.createServer(function(request, response) {
    var parseUrl = url.parse(request.url);
    var parseQuery = querystring.parse(parseUrl.query,'&','=');
    var addressCheck = compareAddress("127.0.0.1", request.connection.remoteAddress);
    console.log("\t[-] Request IP : " + request.connection.remoteAddress);
    console.log("\t[-] Request URL : " + encodeURI(request.url));

    if(request.url == "/" && !addressCheck) {
        response.writeHead(200, {"Content-Type":"text/html"});
        response.write("<h3>How to request '/' in Server Side?</h3>\n");
        response.write("<form method='GET' action='/'>\n");
        response.write("\t<input type=hidden id='url' name='url' value='/' />\n");
        response.write("\t<input type=submit value='Submit'/>\n")
        response.write("</form>\n");
        response.end("");
    } else if (request.url == "/" && addressCheck) {
        response.writeHead(200, {"Content-Type":"text/html"});
        response.write("Flag : <font color='blue'/>" + flag + "</font>");
        response.end("");
    } else if (parseQuery.url && parseQuery.url != "/") {       
        try {
            var options = { host: hostname, port: port, path: parseQuery.url };
            var req = http.get(options, function(res) {
                var bodyChunks = [];
                var resbody = '';
                res.on('data', function(chunk) {
                    bodyChunks.push(chunk);
                }).on('end', function() {
                    resbody = '' + Buffer.concat(bodyChunks);
                    response.writeHead(200, {"Content-Type":"text/html"});
                    response.write(resbody);
                    response.end("");
                });   
            });
            req.on('error', function(e) {
                response.writeHead(400, {"Content-Type":"text/html"});
                response.write("<h3>Bad...</h3>");
                response.end("");
            });

        } catch (err) {
            responseError(response, parseQuery.url);
        }
    } else {
        responseError(response, request.url);
    }
});
  

var port = 37777;
var hostname = "0.0.0.0";

server.listen(port, hostname, function() {
    console.log("[+] Server is running...");
    console.log("[+] Hostname : " + hostname);
    console.log("[+] Port : " + port);
});
