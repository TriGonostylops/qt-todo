# Qt Kanban TODO App

This is a simple Kanban-style TODO application built with Qt. It allows users to manage tasks across three stages: **To Do**, **In Progress**, and **Done**. Tasks can be tagged, edited, and saved to or loaded from a JSON file.

## Features

-  **Three-column Kanban layout**
  - Tasks are categorized into "To Do", "In Progress", and "Done" sections.
-  **Add/Edit/Delete Tasks**
  - Each task has a title, due date, status, and optional tags.
-  **Load/Save Functionality**
  - Save tasks to a JSON file.
  - Load tasks from a JSON file (option to merge or replace existing ones).
-  **Dialog Window**
  - Dedicated dialog for task creation and editing (beyond native Open/Save).

## Structure

- `main.cpp` – Entry point of the application.
- `mainwindow.[h|cpp|ui]` – Handles the main GUI and logic.
- `task.h` – Defines the `Task` struct and `Status` enum.
- `taskdialog.[h|cpp|ui]` – Dialog window for adding/editing a task.

## Build Instructions

1. Open the project with **Qt Creator**.
2. Ensure you have **Qt 5 or 6** installed.
3. Click **Build** and then **Run**.

## File Format

Tasks are saved as an array of JSON objects:

```json
[
  {
    "title": "Finish report",
    "dueDate": "2025-05-25",
    "status": "ToDo",
    "tags": ["urgent", "work"]
  }
]
