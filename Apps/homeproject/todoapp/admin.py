from django.contrib import admin
from . import models
# Register your models here.

admin.site.register(models.Todoitem)
admin.site.register(models.Todolist)
