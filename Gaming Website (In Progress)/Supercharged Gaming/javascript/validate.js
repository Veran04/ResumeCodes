function validateForm()
{
     //here we make sure that the first name has data, and more than one character.
    if(document.myform.fname.value=="")
    {
        alert("first name cannot be empty");
        return false;
    }

    if(document.myform.fname.value.length<2)
    {
        alert("first name must be more than one character");
        return false;
    }


    //here we make sure that the last name has data, and more than one character.
    if(document.myform.lname.value=="")
    {
        alert("last name cannot be empty");
        return false;
    }

    if(document.myform.lname.value.length<2)
    {
        alert("last name must be more than one character");
        return false;
    }


    //here we make sure that the address has data, and more than one character.
    if(document.myform.addr.value=="")
    {
        alert("address cannot be empty");
        return false;
    }

    if(document.myform.addr.value.length<2)
    {
        alert("address must be more than one character");
        return false;
    }

    //here we make sure that the city has data, and more than one character.
    if(document.myform.city.value=="")
    {
        alert("city cannot be empty");
        return false;
    }

    if(document.myform.city.value.length<2)
    {
        alert("city must be more than one character");
        return false;
    }

    //here we make sure that a state was selected
    var state = document.getElementById("state-select");
        if (state.value == "") {
            //If the "Please Select" option is selected display error.
            alert("Please select a state");
            return false;
        }

    //here we make sure that a zip was entered
    if(document.myform.zip.value=="")
    {
        alert("zip code cannot be empty");
        return false;
    }

    
//here we make sure that the zip code is a number
if(isNaN( document.myform.zip.value )) 
{
alert( "The zip code should only contain numbers" );
return false;
}

 //here we make sure the length of the zip code is 5
 if(document.myform.zip.value.length != 5) 
 {
alert( "The zip code should be exactly 5 digits long" );
return false;
 }

 

    //here we make sure that a phone # was entered
    if(document.myform.phone.value=="")
    {
        alert("phone number cannot be empty");
        return false;
    }


    //here we make sure that the phone number is a number
if(isNaN( document.myform.phone.value )) 
{
alert( "The phone number should only contain numbers" );
return false;
}

 //here we make sure the length of the phone number is 10
 if(document.myform.phone.value.length != 10) 
 {
alert( "The phone number should be exactly 10 digits long" );
return false;
 }


      //here we make sure that a radio button is ticked
      if(!document.getElementById('business').checked && !document.getElementById('personal').checked) {
        alert("must select a phone type");
        return false;
      }

    //here we make sure that a email was entered
    if(document.myform.email.value=="")
    {
        alert("email cannot be empty");
        return false;
    }


    
    //here we validate the requirements of the email involving '@' and '.' as described in rubric
    var emailID = document.myform.email.value;
atpos = emailID.indexOf("@");
dotpos = emailID.indexOf(".");
if(atpos <= -1){
    alert("email needs to contain an ampersand");
    return false;
}
//uses the length of the email compared with the position of the @ instead of using a regex
else if(atpos > -1){
    if(emailID.length <= atpos+1){
        alert("email needs to contain a character after the ampersand");
        return false;
    }
}

if(dotpos <= -1){
    alert("email needs to contain a period");
    return false;
}
else if(dotpos > -1){
    if(emailID.length <= dotpos+1){
        alert("email needs to contain a character after the period");
        return false;
    }
}
      
  
    //if no errors are found, we allow the user to submit their data
    else
    {
        return true;
    }

}