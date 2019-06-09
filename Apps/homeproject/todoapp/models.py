from django.db import models

# Create your models here.

class Todolist(models.Model):
    name=models.CharField(max_length=20)
    created=models.DateField(auto_now_add=True)

class Todoitem(models.Model):
    description=models.CharField(max_length=200)
    due_date=models.DateField(null=True)
    completed=models.BooleanField(default=False)
    list_id=models.ForeignKey(Todolist,on_delete=models.CASCADE)