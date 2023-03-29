// CREATE

// add a contact to the user's contactlist
function addContact() {
    // get values from form
    let addFirstName = $("#addFirstName").val();
    let addLastName = $("#addLastName").val();
    let addPhoneNumber = $("#addPhoneNumber").val();
    let addEmail = $("#addEmail").val();

    $("#checkEmail").html("");
    $("#checkPhone").html("");

    // make sure there is no empty string
    if (addFirstName && addLastName && addPhoneNumber && addEmail) {
        // validate email and phone
        if (!validateEmail(addEmail)) {
            $("#checkEmail").html("Invalid Email Address");
        }
        if (!validatePhone(addPhoneNumber)) {
            $("#checkPhone").html("Invalid Phone Number");
        }
        if (!validatePhone(addPhoneNumber) || !validateEmail(addEmail)) {
            return;
        }

        readCookie();

        // create object to send to API
        let jsonPayload = JSON.stringify({
            firstName: addFirstName,
            lastName: addLastName,
            phone: addPhoneNumber.replace(/\D/g, ''),
            email: addEmail,
            userID: userID,
        });

        let url = baseURL + '/AddContact.' + extension;
        let xhr = new XMLHttpRequest();
        xhr.open("POST", url, true);
        xhr.setRequestHeader("Content-type", "application/json; charset=UTF-8");

        try {
            xhr.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    let jsonObject = JSON.parse(xhr.responseText);

                    if (jsonObject.error.localeCompare("Contact Exists") === 0) {
                        $("#checkContact").text(`Contact ${addFirstName} ${addLastName} already exists.`);
                        return;
                    }

                    // notify user of operation success or failure
                    if (jsonObject.error) {
                        toastr.error(`Failed to Add ${addFirstName} ${addLastName} to Contacts List.`);
                    } else {
                        toastr.success(`Added ${addFirstName} ${addLastName} to Contacts List!`);
                        $('#addContact').modal("toggle");
                        // searchFuntion();
                    }
                }
            };
            // post payload to API
            xhr.send(jsonPayload);
        } catch (err) {
            $("#contactsList").html(err.message);
        }

        // clears form after submission
        $('#addForm').each(function () {
            this.reset();
        });
    }
}

// READ

// search function called on click of the search bar button,
// it should take the input and userID and post to the API
function searchFuntion() {
    // get userID
    readCookie();

    //  get search bar input
    let searchResult = $("#searchBar").val();

    // create package sent to API
    let jsonPayload = JSON.stringify({
        userID: userID,
        search: searchResult.replace(/\s\s+/g, ' '),
    });

    // Get data from API
    let url = baseURL + '/SearchContacts.' + extension;

    let xhr = new XMLHttpRequest();
    xhr.open("POST", url, true);
    xhr.setRequestHeader(
        "Content-type",
        "application/json; charset=UTF-8"
    );

    try {
        // let the user know what is happening
        toastr.info("Gathering Contacts!");
        xhr.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                $("#contacts").html("Contact(s) List");

                let jsonObject = JSON.parse(xhr.responseText);

                $('#contactsTable').DataTable().destroy();

                // build the table for the contacts
                buildTable(jsonObject.contacts, jsonObject.contacts.length);

                $('#contactsTable').DataTable({
                    "retrieve": true,
                    "pagingType": "simple_numbers", // "simple" option for 'Previous' and 'Next' buttons only
                    "searching" : false
                });
            }
        };
        xhr.send(jsonPayload);
    } catch (err) {
        $("#contactsList").html(err.message);
    }

}

// build contacts table in html using the data array
function buildTable(data, numContacts) {
    table = $('#contactsTableBody');
    table.html('');

    for (var i = 0; i < numContacts; i++) {
        phoneNum = formatPhoneNumber(data[i].Phone);

        $('<tr>').attr('role', 'row').append(
            $('<td>').text(data[i].FirstName).attr('role', 'cell'),
            $('<td>').text(data[i].LastName).attr('role', 'cell'),
            $('<td>').text(data[i].Email).attr('role', 'cell'),
            $('<td>').text(phoneNum).attr('role', 'cell'),
            $('<td>').html(
                `<button
                    type='button' class='btn' data-toggle='modal'
                    onclick="deleteContact(
                        ${data[i].ID},
                        '${data[i].FirstName}',
                        '${data[i].LastName}');">
                    <span style='color: tomato' class='fas fa-trash-alt'></span></button>
                <button type='button' class='btn' data-toggle='modal' data-target="#editContact"
                    onclick="initEditContact(
                        ${data[i].ID},
                        '${data[i].FirstName}',
                        '${data[i].LastName}',
                        '${data[i].Phone}',
                        '${data[i].Email}');">
                    <span style='color: gray' class='fas fa-cog'></span></button>`).attr('role', 'cell')
        ).appendTo(table);
    }

    // update search result count at top of the table
    $('#numResults').text(`${numContacts} matching result${(numContacts > 1 || numContacts === 0) ? "s" : ""}`);

    // Let the user know that the gathering process is finished
    toastr.success(`Finished Gathering ${numContacts} Contact${(numContacts > 1 || numContacts === 0) ? "s" : ""}!`);
}

// UPDATE

// runs when the edit modal opens and fills in each of the input
// boxes with the current values of the contact
function initEditContact(editContactID, firstName, lastName, phone, email) {
    // fill with current values
    $("#editFirstName").val(firstName);
    $("#editLastName").val(lastName);
    $("#editPhoneNumber").val(formatPhoneNumber(phone));
    $("#editEmail").val(email);

    // set up edit button to call the accual edit function
    // that validates the email/phone then posts to the API
    $("#editButton").attr("onclick", `editContact("${editContactID}")`);

    $("#checkEmail2").html("");
    $("#checkPhone2").html("");
}

function editContact(editContactID) {
    readCookie();
    let editFirstName = $("#editFirstName").val();
    let editLastName = $("#editLastName").val();
    let editPhoneNumber = $("#editPhoneNumber").val();
    let editEmail = $("#editEmail").val();

    if (!validateEmail(editEmail)) {
        $("#checkEmail2").html("Invalid Email Address");
    }
    if (!validatePhone(editPhoneNumber)) {
        $("#checkPhone2").html("Invalid Phone Number");
    }
    if (!validatePhone(editPhoneNumber) || !validateEmail(editEmail)) {
        return;
    }

    let jsonPayload = JSON.stringify({
        firstName: editFirstName,
        lastName: editLastName,
        phone: editPhoneNumber.replace(/\D/g, ''),
        email: editEmail,
        contactID: editContactID,
        userID: userID,
    });

    let url = baseURL + '/UpdateContact.' + extension;
    let xhr = new XMLHttpRequest();
    xhr.open("POST", url, true);
    xhr.setRequestHeader("Content-type", "application/json; charset=UTF-8");
    try {
        xhr.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                let jsonObject = JSON.parse(xhr.responseText);

                if (jsonObject.error) {
                    toastr.error("Failed to Update Contact.");
                } else {
                    toastr.success("Updated Contact!");
                    // clears form after submission
                    $('#editContact').modal("toggle");
                    $('#editForm').each(function () {
                        this.reset();
                    });

                    // searchFuntion();
                }
            }
        };
        xhr.send(jsonPayload);
    } catch (err) {
        $("#contactsList").html(err.message);
    }
}

// DELETE

// delete the contact with confirmation
function deleteContact(contactID, firstName, lastName) {
    if (confirm(`Are you sure you want to delete ${firstName} ${lastName}?`)) {
        // get userID
        readCookie();

        // create object to send to API
        let jsonPayload = JSON.stringify({
            contactID: contactID,
            userID: userID,
        });

        // prepare post to API
        let url = baseURL + '/RemoveContact.' + extension;
        let xhr = new XMLHttpRequest();
        xhr.open("POST", url, true);
        xhr.setRequestHeader("Content-type", "application/json; charset=UTF-8");
        try {
            xhr.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    let jsonObject = JSON.parse(xhr.responseText);

                    // notify user of succes or failure
                    if (jsonObject.error) {
                        toastr.error(`Failed to Remove ${firstName} ${lastName} from Contacts List.`);
                    } else {
                        toastr.success(`Removed ${firstName} ${lastName} from Contacts List!`);
                        // searchFuntion();
                    }
                }
            };
            // post to API
            xhr.send(jsonPayload);
        } catch (err) {
            $("#contactsList").html(err.message);
        }
    }
}

$(document).ready(function () {
    document.title = document.title + TITLE_STR;

    readCookie();

    // welcome the user on page load
    toastr.info("", `Welcome back ${firstName} !`, {
        positionClass: "toast-top-center"
    });

    $("#cancelAdd").on("click", function (event) {
        $('#addContact').modal("toggle");
        // clears form after submission
        $('#addForm').each(function () {
            this.reset();
        });
    });

    $("#cancelEdit").on("click", function (event) {
        $('#editContact').modal("toggle");
        // clears form after submission
        $('#editForm').each(function () {
            this.reset();
        });
    });

    // allow user to use enter key to submit
    $("#searchBtn").on("click", function (event) {
        searchFuntion();
    });

    // allow user to use enter key to submit
    $("#searchBar").on("keyup", function (event) {
        if (event.keyCode === 13) {
            $("#searchBtn").click();
        }
    });

    $("#editForm input").on("keyup", function (event) {
        if (event.keyCode === 13) {
            $("#editButton").click();
        }
    });

    $("#addForm input").on("keyup", function (event) {
        if (event.keyCode === 13) {
            $("#addButton").click();
        }
    });
})
