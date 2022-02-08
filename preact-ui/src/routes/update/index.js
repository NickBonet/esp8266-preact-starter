import { h } from "preact";
import style from "./style.css";
import { useState, useRef } from "preact/hooks";

const Update = () => {
  const inputFileRef = useRef(null);
  const [fileName, setFileName] = useState("test");
  const [updateResponse, setUpdateResponse] = useState("");

  const onSelectProgramFile = () => {
    inputFileRef.current.click();
  };

  const onFileNameChange = () => {
    const current = inputFileRef.current;
    if (current && current.files.length > 0) {
      console.log(current.files[0]);
      setFileName(current.files[0].name);
    }
  };

  const onUploadFile = async () => {
    const current = inputFileRef.current;
    if (current && current.files.length > 0) {
      let data = new FormData();
      data.append("file", current.files[0]);

      const response = await fetch("/update", {
        method: "POST",
        body: data
      });

      const responseCode = await response.status;
      if (responseCode == 200) {
        setUpdateResponse("Successful update!");
      }
    }
  };

  return (
    <div class={style.update}>
      <h1>OTA Update</h1>
      <p>Current filename: {fileName}</p>
      <button onClick={onSelectProgramFile}>Select Program File</button>
      <input
        type="file"
        ref={inputFileRef}
        onChange={onFileNameChange}
        style={{ display: "none" }}
        accept=".bin"
      />
      <br />
      <br />
      <button onClick={onUploadFile}>Upload Program File</button>
      <br />
      <p>Update result: {updateResponse}</p>
    </div>
  );
};

export default Update;
