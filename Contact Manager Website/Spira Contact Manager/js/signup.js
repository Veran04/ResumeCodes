$(document).ready(function () {
    document.title = "Sign Up" + TITLE_STR;

    $(function () {
        $("form[name='registration']").validate({
            rules: {
                firstname: {
                    required: true,
                },
                lastname: {
                    required: true,
                },
                username1: {
                    required: true,
                },
                password1: {
                    required: true,
                    minlength: 8,
                },
                passwordConfirm: {
                    equalTo: "#password1",
                },
            },

            messages: {
                firstname: "Please enter your First Name",
                lastname: "Please enter your Last Name",
                username1: "Please enter a valid Username",
                password1: {
                    required: "Please provide a password",
                    minlength: "Your password must be at least 8 characters long",
                },
                passwordConfirm: {
                    equalTo: "Your passwords do not match",
                },
            },

            submitHandler: function (form) {
                userID = 0;
                firstName = $("#firstname").val();
                lastName = $("#lastname").val();

                let login = $("#username1").val();
                let password = md5($("#password1").val());

                $("#signupResult").html("");

                let obj = {
                    login: login,
                    password: password,
                    firstName: firstName,
                    lastName: lastName,
                };
                let jsonPayload = JSON.stringify(obj);

                let url = baseURL + "/Signup." + extension;

                let xhr = new XMLHttpRequest();
                xhr.open("POST", url, true);
                xhr.setRequestHeader(
                    "Content-type",
                    "application/json; charset=UTF-8"
                );
                try {
                    xhr.onreadystatechange = function () {
                        if (this.readyState == 4 && this.status == 200) {
                            let jsonObject = JSON.parse(xhr.responseText);

                            if (jsonObject.error.localeCompare("Invalid Username") === 0) {
                                $("#usernameCheck").html("Username is already taken");
                                return;
                            }

                            userID = jsonObject.id;

                            window.location.href = "index.html";
                        }
                    };
                    xhr.send(jsonPayload);
                } catch (err) {
                    $("#signupResult").html(err.message);
                }
            },
        });
    });
});
