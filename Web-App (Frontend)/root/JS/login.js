function validate() {
    var email = txtemail.value
    regex = /^[a-zA-Z0-9._-]+@vnsgu.[a-zA-Z]{2,4}.[a-zA-Z]{2,4}$/
    if (email == "") {
        document.getElementById("error").innerHTML = "Enter Email"
        return false
    } else {
        if (regex.test(email)) {
            document.getElementById("error").innerHTML = ""

        } else {
            document.getElementById("error").innerHTML = "Invalid Email"
            return false
        }
    }

    var pass = txtpass.value
    regex = /^[a-zA-Z0-9!@#$%^&*]{8,16}$/;
    if (pass == "") {
        document.getElementById("error").innerHTML = "Enter Password"
        return false
    } else {
        if (regex.test(pass)) {
            document.getElementById("error").innerHTML = ""
        } else {
            document.getElementById("error").innerHTML = "Invalid Password"
            return false
        }
    }
}

function validaterpass() {
    var pass = txtpass.value
    var cpass = txtcpass.value
    regex = /^[a-zA-Z0-9!@#$%^&*]{8,16}$/;
    if (pass == "" || cpass == "") {
        document.getElementById("error").innerHTML = "Enter Password"
        return false
    } else {
        if (regex.test(pass)) {
            document.getElementById("error").innerHTML = ""

        } else {
            document.getElementById("error").innerHTML = "Invalid Password"
            return false
        }
    }
    if (pass != cpass) {
        document.getElementById("error").innerHTML = "Password not Match!"
    }
}

function validateotp() {
    var otp = txtotp.value
    regex = /^[0-9]{6}$/;
    if (otp == "") {
        document.getElementById("error").innerHTML = "Enter OTP"
        return false
    } else {
        if (regex.test(otp)) {
            document.getElementById("error").innerHTML = ""
        } else {
            document.getElementById("error").innerHTML = "Invalid OTP"
            return false
        }
    }
}