# Generated by Django 2.1.2 on 2019-06-17 06:54

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('newapp', '0010_match_match_id'),
    ]

    operations = [
        migrations.RenameField(
            model_name='deliveries',
            old_name='innings',
            new_name='inning',
        ),
    ]