from pymongo import MongoClient
from bson.objectid import ObjectId

class AnimalShelter(object):
    """ CRUD operations for Animal collection in MongoDB """

    def __init__(self, username, password):
        # Initializing the MongoClient. This helps to 
        # access the MongoDB databases and collections. 
        self.client = MongoClient('mongodb://%s:%s@localhost:39001/?authMechanism=DEFAULT&authSource=AAC' % (username, password))
        self.database = self.client['AAC']

# Complete this create method to implement the C in CRUD.
    def create(self, data):
        if data is not None:
            self.database.animals.insert(data)  # data should be dictionary   
            return True
        else:
            raise Exception("Nothing to save, because data parameter is empty")

# Create method to implement the R in CRUD.
    def read(self, data):
        # point to a list of results
        pointer = self.database.animals.find(data, {'_id':False})
        # display results
        return pointer
    
# Update method
    def update(self, data, new_data):
        if data is not None:
            if new_data is not None:
                self.database.animals.update_one(data,{"$set":new_data})
                return True
            else:
                raise Exception("Updated data cannot be blank")
        else:
            raise Exception("Could not find document to update")

# Delete Method
    def delete(self, data):
        if data is not None:
            self.database.animals.delete_one(data)
            return True
        else:
            raise Exception("Could not find document to delete")
