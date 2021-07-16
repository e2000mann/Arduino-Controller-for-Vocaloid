-- Synthesizer V code

function getClientInfo()
    return {
        name = "Arduino Voice Synth Controller (Synth V)",
        category = "Test",
        author = "Emma Mann",
        versionNumber = 0,
        minEditorVersion = 65540
    }
end

function main()
    SV:showMessageBox("Welcome", "Please use your Arduino setup to input notes")

    local project = SV:getProject()
    local newGroup = SV:create("NoteGroup")
    local newGroupRef = SV:create("NoteGroupReference")

    project:addNoteGrooup(newGroup, 1)
    newGroupRef:setTarget(newGroup)
    project:getTrack(1):addGroupReference(newGroupRef)

    -- change to run when select button pressed on arduino circuit
    createNote()
end

function createNote()
    local newGroup = SV:getProject():getNoteGroup(1)

    local note = SV:create("Note")
    note.setDuration(t)
    note.setLyrics(lyrics)
    note.setPitch(pitch) -- midi number
    -- how to work out offset?
    note.setOffset(offset)
    
    newGroup:addNote(n)
end