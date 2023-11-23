function fetchLocalJsonData(filePath) {
    fetch(filePath)
        .then(response => {
            if (!response.ok) {
                throw new Error('Network response was not ok ' + response.statusText);
            }
            return response.json();
        })
        .then(data => {
            console.log(data);
            // Vous pouvez manipuler vos données JSON ici
        })
        .catch(error => {
            console.error('Problem with fetch operation:', error);
        });
}

// Exemple d'utilisation
fetchLocalJsonData('data.json');