$(document).ready(function () {
    document.title = 'Login' + TITLE_STR;

    $(function () {
        $("form[name='login']").validate({
            rules: {
                username: {
                    required: true,
                },
                password: {
                    required: true,
                },
            },
            messages: {
                username: "Please enter a valid email address",

                password: {
                    required: "Please enter your password",
                },
            },
            submitHandler: function (form) {

                userID = 0;
                firstName = "";
                lastName = "";

                let login = $("#username").val();
                let password = $("#password").val();

                $("#loginResult").html("");

                let obj = {
                    login: login,
                    password: md5(password)
                    // password: password
                };
                let jsonPayload = JSON.stringify(obj);


                let url = baseURL + '/Login.' + extension;

                let xhr = new XMLHttpRequest();
                xhr.open("POST", url, true);
                xhr.setRequestHeader("Content-type", "application/json; charset=UTF-8");
                try {
                    xhr.onreadystatechange = function () {
                        if (this.readyState == 4 && this.status == 200) {
                            let jsonObject = JSON.parse(xhr.responseText);
        
                            userID = jsonObject.id;
        
                            if (userID < 1) {
                                $("#loginResult").html("User/Password combination is incorrect");
                                return;
                            }
        
                            firstName = jsonObject.firstName;
                            lastName = jsonObject.lastName;
        
                            saveCookie();
        
                            window.location.href = "main.html";
                        }
                    };
                    xhr.send(jsonPayload);
                } catch (err) {
                    $("#loginResult").html(err.message);
                }
            }
        });
    });
});
