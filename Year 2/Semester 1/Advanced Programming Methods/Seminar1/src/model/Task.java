package model;

import java.util.Objects;

public abstract class Task {
    public String getTaskID() {
        return taskID;
    }

    public void setTaskID(String taskID) {
        this.taskID = taskID;
    }

    public String getDescriere() {
        return descriere;
    }

    public void setDescriere(String descriere) {
        this.descriere = descriere;
    }

    private String taskID;
    private String descriere;

    public Task(String _taskID, String _descriere) {
        taskID = _taskID;
        descriere = _descriere;
    }

    public abstract void execute();

    @Override
    public String toString() {
        return this.taskID + " " + this.descriere;
    }

    @Override
    public boolean equals(Object obj) {
        if (this==obj) return true;
        if (!(obj instanceof Task)) return false;
        Task task=(Task) obj;
        return (Objects.equals(getTaskID(),task.getTaskID()) && Objects.equals(getDescriere(), task.getDescriere()));
    }

    @Override
    public int hashCode() {
        return Objects.hash(getTaskID(),getDescriere());

    }
}
