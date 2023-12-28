import datetime

reminders = []

def set_reminder(task, time):
    reminder = {"task": task, "time": time}
    reminders.append(reminder)
    print(f"Reminder set: {task} at {time}")

def check_reminders():
    now = datetime.datetime.now()
    for reminder in reminders:
        if reminder["time"] <= now:
            print(f"Reminder: {reminder['task']}")
            reminders.remove(reminder)

# Example usage
set_reminder("Meeting with client", datetime.datetime(2023, 12, 1, 15, 30))
check_reminders()
